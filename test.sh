echo "Running tests..."
echo

N=100

echo "Running Collatz of $N"
./main $N 1 100 LRU 40

if [ $? -eq 0 ]; then
    echo "All tests passed."
else
    echo "There are errors."
fi
