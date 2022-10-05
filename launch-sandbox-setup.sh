source setup-sanbox.sh
source CommonVariables.sh

confirmDownload

setupCURL

if [[ $? -lt 0 ]]; then 
    echo -e "${RED_C} --MajorTask@SetupCURL : Failed setting up CURL, check your connection."
	exit $?
else 
    echo -e "${GREEN_C} --MajorTask@SetupCURL : Curl Successfully settled up and ready to run."
fi

echo -e ${RESET_Cs}

if [[ `downloadAvrToolChain` -lt 0 ]]; then 
    echo -e "${RED_C} --MajorTask@Download-AvrGCC : Failed downloading avr toolchains, check your connection."
	exit $?
else 
    echo -e "${GREEN_C} --MajorTask@Download-AvrGCC : Avr toolchains archive successfully downloaded."
fi

echo -e ${RESET_Cs}

if [[ `extractCompressedFile $avrgcc_compressed` -lt 0 ]]; then
    echo -e "${RED_C} --MajorTask@Extract-AvrGCC : Failed extracting avr toolchains, check your storage."
	exit $?
else 
    echo -e "${GREEN_C} --MajorTask@Extract-AvrGCC : Avr toolchains successfully extracted."
fi

echo -e ${RESET_Cs}

if [[ `downloadJdk` -lt 0 ]]; then
    echo -e "${RED_C} --MajorTask@Download-JDK-19 : Failed downloading jdk-19, check your connection."
	exit $?
else 
    echo -e "${GREEN_C} --MajorTask@Download-JDK-19 : jdk-19 archive is downloaded successfully."
fi

echo -e ${RESET_Cs}

if [[ `extractCompressedFile $jdk_compressed` -lt 0 ]]; then
    echo -e "${RED_C} --MajorTask@Extract-JDK-19 : Failed extracting jdk-19 archive, check your storage."
	exit $?
else 
    echo -e "${GREEN_C} --MajorTask@Extract-JDK-19 : jdk-19 archive toolchains successfully extracted."
fi

echo -e ${RESET_Cs}

if [[ `deleteAvrToolchainsArchive` -lt 0 ]]; then
    echo -e "${RED_C} --MajorTask@Release-AVR-GCC-Archive : Failed deleting avr-gcc archive, archive not found."
	exit $?
else 
    echo -e "${GREEN_C} --MajorTask@Release-AVR-GCC-Archive : AVR-GCC archive has been deleted successfully."
fi

echo -e ${RESET_Cs}

if [[ `deleteJdkArchive` -lt 0 ]]; then
    echo -e "${RED_C} --MajorTask@Release-JDK-19-Archive : Failed deleting jdk-19 archive, archive not found."
	exit $?
else 
    echo -e "${GREEN_C} --MajorTask@Release-JDK-19-Archive : jdk-19 archive has been deleted successfully."
fi
