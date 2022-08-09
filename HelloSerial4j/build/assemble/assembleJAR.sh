#**
#* Ccoffee Build tool, manual build, alpha-v1.
#* Custom Includsions for GTKmm cpp wrapper
#* dependencies '-I"/usr/include/glibmm-2.9.1/glib" -I"/usr/include/sigc++-2.0/sigc++" -I"/usr/include/giomm-2.4" -I"/usr/include/gtkmm-4.2.0/gtk"'
#*
#* @author pavl_g.
#*# 

# Sanity check the build directory
source variables.sh

if [[ ! -d $javabuild_directory ]]; then 
    chmod +x $project_root'/build/compile/compile.sh'
    cd $project_root'/build/compile'
    ./'compile.sh'
fi

echo "Assemble JAR"
echo -e $RESET_Cs
echo "--------Script start--------"
cd $project_root'/build/assemble'
source script.sh
source clean.sh

clean=`clean`
if (( clean > 0 )); then 
    echo -e "$RED_C Task@Clean : Failed"
else 
    echo -e "$CYAN_C Task@Clean : Completed"
fi

echo -e $RESET_Cs

make_output_dir=`makeOutputDir`
if ((  make_output_dir > 0 ));  then
    echo -e "$RED_C Task@MakeOutputDirectory : Failed"
else
    echo -e "$WHITE_C Task@MakeOutputDirectory : Completed"
fi

echo -e $RESET_Cs

create_manifest=`createManifest`
if (( create_manifest > 0 )); then
    echo -e "$RED_C Task@CreateJarManifest : Failed"
else
    echo -e "$ORANGE_C Task@CreateJarManifest : Completed"
fi

echo -e $RESET_Cs

add_dependencies=`addDependencies`
if (( add_dependencies > 0 )); then
    echo -e "$RED_C Task@AddJavaDependencies : Failed"
else
    echo -e "$ORANGE_C Task@AddJavaDependencies : Completed"
fi

echo -e $RESET_Cs

add_natives=`addDesktopNativeDependencies`
if (( add_natives > 0 )); then 
    echo -e "$RED_C Task@AddDesktopNativeDependencies : Failed"
else
    echo -e "$MAGNETA_C Task@AddDesktopNativeDependencies : Completed"
fi

echo -e $RESET_Cs

add_android_natives=`addAndroidNativeDependencies`
if (( add_android_natives > 0 )); then 
    echo -e "$RED_C Task@AddNativeDependencies : Failed"
else
    echo -e "$MAGNETA_C Task@AddNativeDependencies : Completed"
fi

echo -e $RESET_Cs

add_assets=`addAssets`
if (( add_assets > 0 )); then 
    echo -e "$RED_C Task@AddAssets : Failed -- AssetsNotFound"
else
    echo -e "$ORANGE_C Task@AddAssets : Completed"
fi

echo -e $RESET_Cs

create_jar=`createJar`
if (( create_jar > 0 )); then 
    echo -e "$RED_C Task@CreateJar : Failed"
else
    echo -e "$ORANGE_C Task@CreateJar : Completed"
fi

echo -e $RESET_Cs

echo "--------Script end--------"
