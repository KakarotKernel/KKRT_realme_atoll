#!/bin/bash

echo "Setting Up Environment"
echo ""
export ARCH=arm64
export SUBARCH=arm64
export KBUILD_BUILD_USER=neel0210
export KBUILD_BUILD_HOST=Catelina

# Variables
export Image="$(pwd)/out/arch/arm64/boot/Image.gz-dtb"
export TC="/home/neel/Desktop/toolchain/"
export VMTC="$(pwd)/clang"

START(){
	# Calculate compilation time
	START=$(date +"%s")
}
#
END(){
	END=$(date +"%s")
	DIFF=$((END - START))
	echo -e "Kernel has been compiled successfully and it took $((DIFF / 60)) minute(s) and $((DIFF % 60)) second(s)"
	echo "Done!"
}

# Enforcing
RUI="AOSP_atoll_defconfig"
clear
echo "---------------------------"
echo checking if bulding offline
echo "---------------------------"
if [ -d "$TC" ]; then
	echo "building offline; thus exporting paths"
	export CROSS_COMPILE=/home/neel/Desktop/toolchain/19/bin/aarch64-linux-android-
	export CLANG_TRIPLE=/home/neel/Desktop/toolchain/14/bin/aarch64-linux-gnu-
	export CC=/home/neel/Desktop/toolchain/14/clang
	export CROSS_COMPILE_ARM32=/home/neel/Desktop/toolchain/1932/bin/arm-linux-androideabi-	
	export CCACHE_EXEC="/usr/bin/ccache"
	export USE_CCACHE=1
	ccache -M 50G
	export CCACHE_COMPRESS=1
	export CCACHE_DIR="/home/neel/Desktop/ccache/.ccache"
else
	echo "Not finding Toolchains at Home/toolchains; thus clonning them; would take some couple of minutes"
	if [ -d "$VMTC" ]; then
		echo exporting paths
		export CROSS_COMPILE=$(pwd)/linaro/bin/aarch64-linux-android-
		export CROSS_COMPILE_ARM32=$(pwd)/gcc32/bin/arm-linux-androideabi-
		export CLANG_TRIPLE=$(pwd)/clang/bin/aarch64-linux-gnu-
		export CC=$(pwd)/clang/bin/clang
	else
		git clone --depth=1 https://github.com/LineageOS/android_prebuilts_gcc_linux-x86_aarch64_aarch64-linux-android-4.9 --single-branch -b lineage-19.0 linaro
		git clone --depth=1 https://github.com/LineageOS/android_prebuilts_gcc_linux-x86_arm_arm-linux-androideabi-4.9 --single-branch -b lineage-19.0 gcc32		
		git clone --depth=1 https://github.com/KakarotKernel/clang.git clang
		export CROSS_COMPILE=$(pwd)/linaro/bin/aarch64-linux-android-
		export CROSS_COMPILE_ARM32=$(pwd)/gcc32/bin/arm-linux-androideabi-		
		export CLANG_TRIPLE=$(pwd)/clang/bin/aarch64-linux-gnu-
		export CC=$(pwd)/clang/bin/clang
	fi
fi
clear
echo "========================="
echo "Remove old Kernel Build"
echo "========================="
rm -rf CORE/*.zip
############################################
# If other device make change here
############################################
clear
echo "==============="
echo "Building Clean"
echo "==============="
echo Clean build leftovers
START
make clean && make mrproper
rm -rf out/arch/arm64/boot/Image.gz-dtb
rm -rf KKRT/*.zip
rm -rf KKRT/Image.gz-dtb
clear
echo "==================="
echo "Building Clean for "
echo "==================="
make $RUI O=out CC=clang
make -j$(nproc --all) O=out CC=clang
echo
if [ -f "$Image" ]; then
	echo "Image compiled; packing it"
	cp -r ./out/arch/arm64/boot/Image.gz-dtb ./KKRT/Image.gz-dtb
	rm -rf KKRT/*.zip
	cd KKRT
	. zip.sh
	cd ..
	changelog=`cat KKRT/changelog.txt`
	for i in KKRT/*.zip
	do
	curl -F "document=@$i" --form-string "caption=$changelog" "https://api.telegram.org/bot${BOT_TOKEN}/sendDocument?chat_id=${CHAT_ID}&parse_mode=HTML"
	done
	echo ""
	END
else
    echo "Kernel isnt compiled, letting Neel know"
    curl -F text="Realme 6 pro: Kernel is not compiled, come and check @neel0210" "https://api.telegram.org/bot${BOT_TOKEN}/sendMessage?chat_id=${CHAT_ID}&parse_mode=Markdown"
fi
