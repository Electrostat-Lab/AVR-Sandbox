
# setup variables
avrgcc_compressed='avr-gcc.tar.gz'

jdk_compressed='jdk.tar.gz'

# setup functions to download and extract toolchains/compilers

function setupCURL() {
    sudo apt-get install curl
}

function downloadAvrToolChain() {
    curl https://ww1.microchip.com/downloads/aemDocuments/documents/DEV/ProductDocuments/SoftwareTools/avr8-gnu-toolchain-3.7.0.1796-linux.any.x86_64.tar.gz --output $avrgcc_compressed
}

function downloadJdk() {
    curl https://download.oracle.com/java/19/archive/jdk-19_linux-x64_bin.tar.gz --output $jdk_compressed
}

function extractCompressedFile() {
    local compressedFile=$1
    tar -xf $compressedFile
}

function deleteAvrToolchainsArchive() {
    rm $avrgcc_compressed 
}

function deleteJdkArchive() {
    rm $jdk_compressed
}
