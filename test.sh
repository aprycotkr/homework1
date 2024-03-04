function basic_test() {
    output=$(./hw0 $1 $2 $3)

    if [ $? -eq 0 ] ; then
	echo "Pass: Program exited zero"
    else
	echo "Fail: Program did not exit zero"
	exit 1
    fi

    outputd=$(./hwdiff $3 $4 0.00001)
    if [ $? -eq 0 ] ; then
	echo "Pass: Output is correct"
    else
	echo "Expected output X.dat is not correct"
	exit 1
    fi
}

function missed_arg() {
    $1 $2 $3 $4 $5 2> temp.txt
    if [ $? -eq 0 ] ; then
	echo "Fail: Program should use 3 args"
	exit 1
    fi
    output=$(cat temp.txt)    
    if [ -z "${output}" ] ; then
	echo "Fail: No error message for incorrent arguments"
	exit 1
    fi        
    if [[ "${output}" != *"Usage"* ]] && [[ "${output}" != *"hw0"* ]] ; then
	echo "Fail: Incorrect error message(${output})"
	exit 1
    fi
}
    
function missed_arg_test() {
    missed_arg "./hw0"
    
    missed_arg "./hw0 A.dat"

    missed_arg "./hw0 A.dat B.dat"

    missed_arg "./hw0 A.dat B.dat X.dat Y.dat"
}

echo "Running tests..."
echo

case $1 in
    "1") basic_test "A.dat" "B.dat" "X.dat" "Xa.dat";;
    "2") basic_test "A2.dat" "B2.dat" "X2.dat" "X2a.dat";;
    "3") basic_test "A3.dat" "B3.dat" "X3.dat" "X3a.dat";;
    "4") missed_arg_test;;
    *) echo "Invalid argument ($1) for the script"
       exit 1;;
esac

echo "Test $1 passed."
exit 0
