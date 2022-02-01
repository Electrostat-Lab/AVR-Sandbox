echo "Ccoffee Script starts"
echo "---------------------------------------------"
export LC_ALL=C
source code.sh

echo -e "${WHITE_C} --MajorTask@Compile : Compiling the project"

echo -e ${RESET_Cs}

if [[ ! `compile` -eq 0 ]]; then
	echo -e "${RED_C} --MajorTask@Compile : Failed compiling sources, exits with errno500."
	exit 500
else 
	echo -e "${GREEN_C} --MajorTask@Compile : Compilation succeeded."
fi
echo -e ${RESET_Cs}

echo -e "${WHITE_C} --MajorTask@Hexing : Creating Hex file"
if [[ ! `convertToHex` -eq 0 ]]; then
	echo -e "${RED_C} --MajorTask@Hexing : Failed to create hex file, exits with errno600."
	exit 600
else 
	echo -e "${GREEN_C} --MajorTask@Hexing : Hex file created successfully."
fi
echo -e ${RESET_Cs}

echo -e "${WHITE_C} --MajorTask@UploadingCode : Uploading Hex file"
if [[ ! `upload` -eq 0 ]]; then
	echo -e "${RED_C} --MajorTask@UploadingCode : Failed to upload hex file, exits with errno700."
	exit 700
else 
	echo -e "${GREEN_C} --MajorTask@UploadingCode : Hex file uploaded successfully."
fi
echo -e ${RESET_Cs}
echo "---------------------------------------------"
echo "Ccoffee Script finishes"
