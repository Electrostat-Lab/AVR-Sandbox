#**
#* Ccoffee Build tool, manual build, alpha-v1.
#*
#* @author pavl_g.
#*#

# Manifest constants
jar_folder='serial4j'
jar=${jar_folder}'.jar'

manifest='Manifest-Version: 1.0'
mainclass='Main-Class: com.serial4j.example.Launcher'
classpath='Class-Path: dependencies'

assemble_dir=`pwd`
# cut the working directory from its end by a one '/' delimiter
build_dir="${assemble_dir%/*}"
# cut the working directory from its end by a one '/' delimiter again
project_root="${build_dir%/*}"

source ${project_root}'/JAVAHOME.sh'
source ${build_dir}'/compile/variables.sh'
source ${project_root}'/CommonVariables.sh'

java_jar=${JAVA__HOME}'/jar'
jar_tmp=$javabuild_directory"/$jar_folder"

