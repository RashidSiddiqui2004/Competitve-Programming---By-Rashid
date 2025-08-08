#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Function to find the best available seat for the current introvert
int findBestSeat(const vector<int> &seats, int N)
{
    int bestSeat = -1;
    int maxDistance = -1;

    // Check all available seats
    for (int i = 0; i < N; i++)
    {
        if (seats[i] == 0)
        { // Seat is empty
            int left = i, right = i;

            // Find the closest occupied seat to the left
            while (left >= 0 && seats[left] == 0)
                left--;
            // Find the closest occupied seat to the right
            while (right < N && seats[right] == 0)
                right++;

            int dist = min(i - left, right - i); // Distance to the closest occupied seat
            if (dist > maxDistance)
            {
                maxDistance = dist;
                bestSeat = i;
            }
        }
    }
    return bestSeat;
}

bool isPossibleToSeat(const vector<int> &P, int N)
{
    vector<int> seats(N, 0);              // Track if a seat is occupied (0 means empty, 1 means occupied)
    vector<int> seatingArrangement(N, 0); // To store the final seating arrangement

    // Simulate the seating process for introverts 1 to N
    for (int introvertID = 1; introvertID <= N; introvertID++)
    {
        int bestSeat = findBestSeat(seats, N);      // Find the best available seat
        seats[bestSeat] = 1;                        // Mark the seat as occupied
        seatingArrangement[bestSeat] = introvertID; // Record the introvert's ID in this seat
    }

    // Now check if the final arrangement matches the given permutation P
    return seatingArrangement == P;
}

int main()
{
    int N;

    // Test case 1
    cin >> N;
    vector<int> P1(N);
    for (int i = 0; i < N; i++)
    {
        cin >> P1[i]; // Read the permutation
    }
    cout << (isPossibleToSeat(P1, N) ? "YES" : "NO") << endl;

    // Test case 2
    cin >> N;
    vector<int> P2(N);
    for (int i = 0; i < N; i++)
    {
        cin >> P2[i]; // Read the permutation
    }
    cout << (isPossibleToSeat(P2, N) ? "YES" : "NO") << endl;

    // Test case 3
    cin >> N;
    vector<int> P3(N);
    for (int i = 0; i < N; i++)
    {
        cin >> P3[i]; // Read the permutation
    }
    cout << (isPossibleToSeat(P3, N) ? "YES" : "NO") << endl;

    return 0;
}
