
# setup variables
avrgcc_compressed='avr-gcc.tar.gz'

jdk_compressed='jdk.tar.gz'

# setup functions to download and extract toolchains/compilers

##
# Prompt the download of the toolchains.
##
function confirmDownload() {

    read -p "This may apply charges, if want to proceed type [1], and [0] or [-N] to terminate ? " command  

    if [[ $command -le 0 ]]; then
        exit 690
    elif [[ ! $command -ge 1 ]]; then
        echo -e 'Command not found'
    fi
}

##
# Sets up the client url utility.
##
function setupCURL() {
    sudo apt-get install curl
    return $?
}

##
# Downloads the avr gcc toolchains from Microchip domains.
# @return 1 for success, 0 for no result, -1 for failure.
##
function downloadAvrToolChain() {
    curl https://ww1.microchip.com/downloads/aemDocuments/documents/DEV/ProductDocuments/SoftwareTools/avr8-gnu-toolchain-3.7.0.1796-linux.any.x86_64.tar.gz --output $avrgcc_compressed
    return $?
}

##
# Downloads jdk-19 from oracle domains.
# @return 1 for success, 0 for no result, -1 for failure.
##
function downloadJdk() {
    curl https://download.oracle.com/java/19/archive/jdk-19_linux-x64_bin.tar.gz --output $jdk_compressed
    return $?
}

##
# Extracts a compressed `.tar.gz` file to this directory.
# @return 1 for success, 0 for no result, -1 for failure.
##
function extractCompressedFile() {
    local compressedFile=$1
    tar --overwrite -xf $compressedFile
    return $?
}

##
# Deletes the avr gcc archive if exists.
# @return 1 for success, 0 for no result, -1 for non-existence.
##
function deleteAvrToolchainsArchive() {
    if [[ ! -e "$avrgcc_compressed" ]]; then
        return -1    
    fi
    rm $avrgcc_compressed 
    return $?
}

##
# Deletes the jdk archive if exists.
# @return 1 for success, 0 for no result, -1 for non-existence.
##
function deleteJdkArchive() {
    if [[ ! -e "$jdk_compressed" ]]; then
        return -1    
    fi
    rm $jdk_compressed
    return $?
}