echo ":clean_coex.sh [begin]"
./clean_coex.sh
echo ":clean_coex.sh [end]"

echo ":build_coex.sh [begin]"
./build_coex.sh > build_log.txt
echo ":build_coex.sh [end]"
