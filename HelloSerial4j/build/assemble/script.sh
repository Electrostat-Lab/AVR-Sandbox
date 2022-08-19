#**
#* Ccoffee Build tool, manual build, alpha-v1.
#*
#* @author pavl_g.
#*#

source variables.sh

#**
#* Makes an output directory at the output location.
#
#* @return the number of errors.
#**
function makeOutputDir() {
    local errors
    cd $javabuild_directory
    if [[ ! -d $jar_folder ]]; then
        if [[ ! `mkdir $jar_folder` -eq 0 ]]; then
            errors=$(( $errors + 1 ))
        fi
    fi
    return $errors
}

#**
#* Creates a Manifest.mf file for the jar main class designation and dependencies inclusion.
#
#* @return the number of errors, 0 if no errors, 1 or 2 if there are errors.
#**
function createManifest() {
    local errors=0
    cd $jar_tmp
    if [[ ! `echo $manifest > Manifest.mf` -eq 0 ]]; then
        errors=$(( $errors + 1 ))
    fi
    if [[ ! `echo $mainclass >> Manifest.mf` -eq 0 ]]; then
        errors=$(( $errors + 1 ))
    fi
    return $errors
}

#**
#* Adds the android native dependencies (the .so native object files) as a jar dependency 
#* at the output/Arithmos/dependencies relative path. 
#
#* @return the number of errors, 0 if no errors, 1 or 2 if there are errors.
#**
function addAndroidNativeDependencies() {
    local errors=0
    # get the object files to link them
    cd $shared_root_dir
    if [[ ! `zip -r $android_natives_jar . -i "lib/*"` -eq 0 ]]; then
        errors=$(( $errors + 1 ))
    fi
    
    android_jar=$shared_root_dir"/$android_natives_jar"
    if [[ $android_jar ]]; then
        # copy the object file to the build dir
        if [[ ! `mv $android_jar $jar_tmp` -eq 0 ]]; then
            errors=$(( $errors + 1 ))
        fi 
    fi
    return $errors
}

#**
#* Adds the linux native dependencies (the .so native object files)
#* at the output/Arithmos relative path. 
#*
#* @return the number of errors, 0 if no errors, 1 or 2 if there are errors.
#**
function addDesktopNativeDependencies() {
    local errors=0
    cd $shared_root_dir
	
    if [[ $shared_root_dir ]]; then
        # copy the object file to the build dir
        if [[ ! `cp -r $shared_root_dir'/native' $jar_tmp` -eq 0 ]]; then
            errors=$(( $errors + 1 ))
        fi   
    fi   
    return $errors
}

function addAssets() {
    local errors=1 
    if [[ -f $assets ]]; then
        if [[ ! `mkdir $jar_tmp'/assets'` -eq 0 ]]; then
            errors=$(( $errors + 1 ))
        fi
        # copy to an asset folder
        cp -r $assets $jar_tmp'/assets'
        cd $jar_tmp
        # zip the assets into a jar file
        if [[ ! `zip -r assets.jar . -i 'assets/*'` -eq 0 ]]; then
            errors=$(( $errors + 1 ))
        fi
        # remove the assets folder
        rm -rf 'assets'
    else 
        errors=$(( $errors + 1 ))
    fi
    return $errors
}

function createJar() {
    local errors=0
    # get the manifest file to link it
    cd $javabuild_directory
    manifest_file=$jar_folder'/Manifest.mf'
    # get the class files ready
    bytecode=`find -name "*.class"`
    # command and output a jar file with linked manifest, java class files and object files
    if [[ ! `$java_jar cmf $manifest_file $jar $bytecode` -eq 0 ]]; then 
        errors=$(( $errors + 1 ))
    fi
    $java_jar uf $jar -C $jar_tmp './native'
	rm -r $jar_tmp'/native/'
    # move the jar to its respective output folder
    mv $jar $jar_tmp
    # move the jar directory containing the jar and the assets to the output directory
    mv $jar_tmp $project_root'/output'
    # remove the residual manifest file
    cd $project_root'/output/'$jar_folder
    rm 'Manifest.mf'
    return $errors
}
