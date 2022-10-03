source setup-sanbox.sh

setupCURL

downloadAvrToolChain

extractCompressedFile $avrgcc_compressed

downloadJdk

extractCompressedFile $jdk_compressed

deleteAvrToolchainsArchive

deleteJdkArchive
