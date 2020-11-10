#include <iostream>

#define MAX_SIZE 100000

struct User
{
	int dateRank;
	int age;
	std::string name;
};

void Swap(User* arr, int i, int j);
void QuickSort(User* arr, int start, int end);

User userList[MAX_SIZE + 1];

int main()
{
	int N = 0;
	std::cin >> N;

	for (int idx = 0; idx < N; idx++)
	{
		int age = 0;
		std::string name;
		std::cin >> age >> name;

		User user;
		user.dateRank = idx;
		user.age = age;
		user.name = name;

		userList[idx] = user;
	}

	QuickSort(userList, 0, N - 1);

	for (int idx = 0; idx < N; idx++)
	{
		std::cout << userList[idx].age << " " << userList[idx].name << "\n";
	}

	return 0;
}

void Swap(User* arr, int i, int j)
{
	User temp = arr[i];
	arr[i] = arr[j];
	arr[j] = temp;
}

void QuickSort(User* arr, int start, int end)
{
	if (start >= end)
		return;

	User pivot = arr[start];
	int left = start + 1;
	int right = end;

	while (left <= right)
	{
		while (left <= end && arr[left].age <= pivot.age)
		{
			if (arr[left].age == pivot.age)
			{
				if (arr[left].dateRank > pivot.dateRank)
					break;
				else
					left++;
			}
			else
				left++;
		}

		while (right > start && arr[right].age >= pivot.age)
		{
			if (arr[right].age == pivot.age)
			{
				if (arr[right].dateRank < pivot.dateRank)
					break;
				else
					right--;
			}
			else
				right--;
		}

		if (left < right)
			Swap(arr, left, right);
		else
			Swap(arr, start, right);
	}

	QuickSort(arr, start, right - 1);
	QuickSort(arr, right + 1, end);
}
