#include<iostream>
#include<stdio.h>
#include<conio.h>
#include<string.h>
#include <bits/stdc++.h>
#define RANGE 255

using namespace std;

int a,b,s,z ,y,arr[100],n,low,high,l,r,x,position;
char q,barr[100];
class SearchAndSort
{
public:
	SearchAndSort();
	void prepareArr();
	void copyArr();
	void print();
	int linearSearch(int); //takes in key for search and returns number of comparisons
	int binarySearch(int); //takes in key for search and returns number of comparisons
	int insertionSort(); //returns number of comparisons
	int selectionSort(); //returns number of comparisons
	int bubbleSort(); //returns number of comparisons
	int mergeSort(); //returns number of comparisons

private:
	static const int size = 100;
	int initialArr[size];
	int sortResult[size];
	int searchResult;
	int mergeSortReccur(int,int); //recursive funtion used for merge sort
	int merge(int,int,int,int); //utility function for the merge sort that merges two sub arrays
};
SearchAndSort::SearchAndSort()
{
	prepareArr();
	copyArr();
}

void SearchAndSort::prepareArr() //fill an array with 100 elements with random values from 0 to 100
{
	srand(time(0)); //time is used as the random seed
	for(int i = 0; i <= size-1;  i++)
	{
		initialArr[i] = rand() % 101; //assigns random number in array
	}
}

void SearchAndSort::copyArr() //copies the values stored in initial array to the sorted result array
{
	for(int i = 0; i <= size-1;  i++)
	{
		sortResult[i] = initialArr[i]; //copies element by element
	}
}

void SearchAndSort::print() //outputs the initial array, sorted result array, and search result
{
	cout << "Initial Array" << endl;
	for(int i = 0; i <= size-1;  i++)
	{
		cout << initialArr[i] << " ";
	}
	cout << endl;

	cout << "Sorted Result Array" << endl;
	for(int i = 0; i <= size-1;  i++)
	{
		cout << sortResult[i] << " ";
	}
	cout << endl;

	cout << "Search Result" << endl;
	cout << searchResult << endl;
}

int SearchAndSort::linearSearch(int key)
{
	copyArr();
	int comparisons = 0;
	searchResult = -1;
	for(int i = 0; i <= size-1; i++) //cycles through each element in the array
	{
		comparisons++;
		if(key == initialArr[i]) //if the value in array matches key then position is stored
		{
			searchResult = i;
			break; //breaks once values is found in array
		}
	}
	return comparisons;
}

int SearchAndSort::binarySearch(int key)
{
	mergeSort(); //binary search requires that the array be sorted before search
	int low = 0;
	int high = size -1;
	int mid = (low + high + 1) / 2;
	int loc = -1;
	int comparisons = 0;

	do{
		if(key == sortResult[mid]) //checks to see if the middle value is equal to the key
		{
			loc = mid; //if so the location is set to middle position
			comparisons++;
		}
		else if(key > sortResult[mid]) //if key is greater than the mid point then the key value must be in the first half of the array if it exists at all
		{
			high = mid - 1; //make the new right bound of array to the left of the midpoint
			comparisons++;
		}
		else //if key is less than the mid point then the key value must be in the second half of the array if it exists at all
		{
			low = mid + 1; //make the new left bound of the array to the right of the midpoint
			comparisons++;
		}

		mid = (low + high + 1) / 2; // the new bid is determined from the new high and low
	}while((low <= high) && (loc == -1)); //runs as long the key has not been found and low does not become greater than high

	searchResult = loc;

	return comparisons;
}

int SearchAndSort::insertionSort()
{
	copyArr();

	int j, insert = 0, comparisons = 0;
	for(int i = 1; i <= size-1; i++)
	{
		comparisons++;
		insert = sortResult[i];
		for( j = i - 1; (j >= 0) && (sortResult[j] < insert); j--) //smaller values move up in the array
		{
			comparisons++;
			sortResult[j+1] = sortResult[j];
		}
		sortResult[j+1] = insert; //put the inserted value in the its the right place to be sorted
	}
	return comparisons;
}

int SearchAndSort::selectionSort()
{
	copyArr();

	int comparisons = 0;
	int first;

	for(int i = size-1; i > 0; i--)
	{
		comparisons++;
		first = 0;
		for(int j = 1; j <= i; j++) //locates smallest between 1 and i
		{
			comparisons++;
			if(sortResult[j] < sortResult[first])
			{
				first = j;
				comparisons++;
			}
		}
		int temp = sortResult[first]; //swaps the smallest with the element in position i
		sortResult[first] = sortResult[i];
		sortResult[i] = temp;
	}
	return comparisons;
}


int SearchAndSort::bubbleSort()
{
	copyArr();
	int comparisons = 0;
	for(int i = 0; i < size-1; i++)
	{
		comparisons++;
		for(int j = 0; j < size-1; j++)
		{
			comparisons++;
			if(sortResult[j+1] > sortResult[j]) //if next element is greater than the current element then swap elements
			{
				comparisons++;
				int temp = sortResult[j]; //swaps the elements
				sortResult[j] = sortResult[j+1];
				sortResult[j+1] = temp;
			}
		}
	}
	return comparisons;
}

int SearchAndSort::mergeSort()
{
	copyArr();
	return mergeSortReccur(0,size-1);  //calls the merge sort recursive function and returns the number of comparisons
}

int SearchAndSort::mergeSortReccur(int low, int high)
{
	int comparisons = 0;
	int mid = 0;
	if((high - low) >= 1)
	{
		comparisons++;
		mid = ((low + high) / 2);
		mergeSortReccur(low, mid); //runs recursive function with first half of array
		mergeSortReccur(mid+1, high); //runs recursive function with second half of the array
		comparisons = comparisons + merge(low, mid, mid+1, high); //call the merge and totals the number of comparisons
	}
	return comparisons;
}

int SearchAndSort::merge(int left, int mid1, int mid2, int right) //merges two sub arrays
{
	int leftIndex = left;
	int rightIndex = mid2;
	int combinedIndex = left;
	int combined[size];
	int comparisons = 0;

	while(leftIndex <= mid1 && rightIndex <= right) //merge arrays until the end of the either array
	{
		comparisons++;
		//places larger of the two current elements into the resulting combined array
		if(sortResult[leftIndex] >= sortResult[rightIndex])
		{
			comparisons++;
			combined[combinedIndex++] = sortResult[leftIndex++];
		}else
		{
			comparisons++;
			combined[combinedIndex++] = sortResult[rightIndex++];
		}
	}

	if(leftIndex == mid2) //if the left array is at end
	{
		comparisons++;
		while(rightIndex <= right) //copy the remaining elements in the right array
		{
			comparisons++;
			combined[combinedIndex++] = sortResult[rightIndex++];
		}
	}else //if the right array is at end
	{
		comparisons++;
		while(leftIndex <= mid1) //copy the remaing elements in the left array
		{
			comparisons++;
			combined[combinedIndex++] = sortResult[leftIndex++];
		}
	}

	//copies values back in the original result array
	for(int i = left; i <= right; i++)
		sortResult[i] = combined[i];

	return comparisons;
}
void insertionSort(int arr[], int n)
              {
                int i, key, j;
                for (i = 1; i < n; i++)
                    {
                      key = arr[i];
                      j = i-1;
                      while (j >= 0 && arr[j] > key)
                            {
                              arr[j+1] = arr[j];
                              j = j-1;
                            }
                      arr[j+1] = key;
                    }
                      for(a=0;a<n;a++)
                                  {
                                      cout<<arr[a];
                                  }
                }
void selectionSort(int arr[], int n)
              {
                int i, j, min;
                for (i = 0; i < n-1; i++)
                    {
                      min = i;
                      for (j = i+1; j < n; j++)
                          if (arr[j] < arr[min])
                             min = j;
                      int t=arr[min];
                      arr[min]=arr[i];
                      arr[i]=t;
                    }
                       for(a=0;a<n;a++)
                                  {
                                      cout<<arr[a];
                                  }
              }
void bubbleSort(int arr[], int n)
              {
                int i, j;
                for (i = 0; i < n-1; i++)
                    {
                      for (j = 0; j < n-i-1; j++)
                          {
                            if (arr[j] > arr[j+1])
                            {
                                int temp=arr[j];
                                arr[j]=arr[i];
                                arr[i]=temp;
                            }

                          }
                    }
                     for(a=0;a<n;a++)
                                  {
                                      cout<<arr[a];
                                  }
              }
int partition(int arr[], int low, int high)
              {
               int pivot = arr[high];
               int i = (low - 1);
               for (int j = low; j <= high- 1; j++)
                   {
                     if (arr[j] <= pivot)
                        {
                          i++;
                          int temp=arr[j];
                          arr[j]=arr[i];
                          arr[i]=temp;

                        }
                   }

                                int temp=arr[i+1];
                                arr[i+1]=arr[high];
                                arr[high]=temp;


               return (i + 1);
             }
void quickSort(int arr[], int low, int high)
              {
                if (low < high)
                   {
                     int pi = partition(arr, low, high);
                     quickSort(arr, low, pi - 1);
                     quickSort(arr, pi + 1, high);
                   }
                   for(a=0;a<n;a++)
                                  {
                                      cout<<arr[a];
                                  }

              }
void cSort(int arr[], int n)
              {
                int output[n];
                int count[RANGE + 1], i;
                memset(count, 0, sizeof(count));
                for(i = 0; arr[i]; ++i)
                    ++count[arr[i]];
                for (i = 1; i <= RANGE; ++i)
                    count[i] += count[i-1];
                for (i = 0; arr[i]; ++i)
                     {
                      output[count[arr[i]]-1] = arr[i];
                      --count[arr[i]];
                    }
                for (i = 0; arr[i]; ++i)
                     arr[i] = output[i];
                     for(a=0;a<n;a++)
                        {
                          cout<<arr[a];
                        }
                     }
void radixsort(int arr[], int n)
              {
                    int mx = arr[0];
                    for (int i = 1; i < n; i++)
                    if (arr[i] > mx)
                       mx = arr[i];

                int m = mx;
                for (int exp = 1; m/exp > 0; exp *= 10)
                    cSort(arr, n);
              }
void bucketSort(int arr[], int n)
              {
     int i, j, k,SIZE, buckets[SIZE];
     cout<<"Enter size of bucket"<<endl;
    cin>> SIZE;


    for(i = 0; i < SIZE; ++i)
        buckets[i] = 0;

    for(i = 0; i < n; ++i)
        ++buckets[arr[i]];

    for(i = 0, j = 0; j < SIZE; ++j)
        for(k = buckets[j]; k > 0; --k)
            arr[i++] = j;
            for(a=0;a<n;a++)
                                  {
                                      cout<<arr[a];
                                  }
}
void merge(int arr[], int l, int m, int r)
              {
                int i, j, k;
                int n1 = m - l + 1;
                int n2 =  r - m;
                int L[n1], R[n2];
                for (i = 0; i < n1; i++)
                    L[i] = arr[l + i];
                for (j = 0; j < n2; j++)
                    R[j] = arr[m + 1+ j];
                i = 0;
                j = 0;
                k = l;
                while (i < n1 && j < n2)
                      {
                        if (L[i] <= R[j])
                           {
                             arr[k] = L[i];
                             i++;
                           }
                        else
                           {
                             arr[k] = R[j];
                             j++;
                           }
                        k++;
                     }
               while (i < n1)
                     {
                       arr[k] = L[i];
                       i++;
                       k++;
                     }
               while (j < n2)
                     {
                       arr[k] = R[j];
                       j++;
                       k++;
                     }
              }
void mergeSort(int arr[], int l, int r)
             {
               if (l < r)
                  {
                    int m = l+(r-l)/2;
                    mergeSort(arr, l, m);
                    mergeSort(arr, m+1, r);
                    merge(arr, l, m, r);
                  }
             }
int search(int arr[], int n, int x)
             {
               int i;
               for (i=0; i<n; i++)
                   if (arr[i] == x)
                      return i;
               return -1;
             }
int binarySearch(int arr[], int l, int r, int x)
             {
               if (r >= l)
                  {
                    int mid = l + (r - l)/2;
                    if (arr[mid] == x)  return mid;
                    if (arr[mid] > x) return binarySearch(arr, l, mid-1, x);
                    return binarySearch(arr, mid+1, r, x);
                  }
               return -1;
             }
int interpolationSearch(int arr[], int n, int x)
             {
               int lo = 0, hi = (n - 1);
               while (lo <= hi && x >= arr[lo] && x <= arr[hi])
                     {
                       int pos = lo + (((double)(hi-lo) /
                                                         (arr[hi]-arr[lo]))*(x - arr[lo]));
                       if (arr[pos] == x)
                       return pos;
                       if (arr[pos] < x)
                       lo = pos + 1;
                       else
                       hi = pos - 1;
                     }
               return -1;
              }
class calc
{
public :
    void in();
    void ans();
};
void calc::in()
{

}
void calc::ans()
{
    A:
    {
        cout<<"IF YOU'D LIKE TO USE PROJECT PRESS 'Y' ELSE TO EXIT PRESS 'N' : \n"<<endl;
        cin>> q;
    }
    while(q!='N')
    {
        cout<<"\n\nFROM THE GIVEN MENU PICK YOUR CHOICE :\n1. SORTING\n2. SEARCHING\n3.Comparison of various sorting and searching methods\n"<<endl;
           int c;
           cin>>c;
    if(q=='Y')
    {

           switch(c)
           {
           case 1:
            {
                cout<<"\n\nFROM THE GIVEN MENU PICK YOUR CHOICE :\n1. INSERTION SORT\n2. SELECTION SORT\n3. BUBBLE SORT\n4. QUICK SORT\n5. COUNT SORT\n6. RADIX SORT\n7. BUCKET SORT\n8. MERGE SORT\n"<<endl;
                cin>>z;
                switch(z)
                {
                    case 1 :
                    {
                        cout<<"\nWhat would you like to choose :\n1.DESCRIPTION \n2.ALGORITHM\n3.EXAMPLE\n"<<endl;
                        cin>>y;
                        switch(y)
                        {
                          case 1 :
                              {
                                  cout<<"Insertion sort:Insertion sort is a simple sorting algorithm that builds the final sorted array (or list) one item at a time \nBest case-O(n)\nWorst case-O(n^2)\nAverage case-O(n^2)"<<endl;
                                   goto A;
                                   break;
                              }
                          case 2 :
                              {
                                  cout<<"passes through each element everything before element is sorted\nputs element in appropriate place in sorted half of array by checking\neach element starting from the back of the sorted part of the array"<<endl;
                                  goto A;
                                  break;
                              }
                          case 3 :
                              {
                                  cout<<"\nEnter the limit of your array :"<<endl;
                                  cin>>n;
                                  cout<<"\nEnter the elements of your array :"<<endl;
                                  for(a=0;a<n;a++)
                                  {
                                      cin>>arr[a];
                                  }
                                 insertionSort(arr, n);
                                  goto A;
                                  break;
                              }
                        }
                        goto A;
                        break;
                    }
                    case 2 :
                    {
                        cout<<"\nWhat would you like to choose : \n1.DESCRIPTION \n2.ALGORITHM\n3.EXAMPLE\n"<<endl;
                        cin>>y;

                        switch(y)
                        {
                          case 1 :
                              {
                                  cout<<"In computer science, selection sort is a sorting algorithm, specifically an in-place comparison sort.\nBest case-O(n^2)\nWorst case-O(n^2)\nAverage case-O(n^2)"<<endl;
                                   goto A;
                                   break;
                              }
                          case 2 :
                              {
                                  cout<<"array to be sorted: A\narray to be returned: B\nfind smallest element in A and put in B\nmark space in A with null so it won’t be chosen again\nrepeat last two steps until B is sorted array"<<endl;
                                  goto A;
                                  break;
                              }
                          case 3 :
                              {
                                  cout<<"\nEnter the limit of your array :"<<endl;
                                  cin>>n;
                                  cout<<"\nEnter the elements of your array :"<<endl;
                                  for(a=0;a<n;a++)
                                  {
                                      cin>>arr[a];
                                  }
                                  selectionSort( arr, n);

                                 goto A;
                                 break;
                              }
                        }
                         goto A;
                         break;
                    }
                    case 3:
                    {
                        cout<<"\nWhat would you like to choose :\n1.DESCRIPTION \n2.ALGORITHM\n3.EXAMPLE\n"<<endl;
                        cin>>y;

                        switch(y)
                        {
                          case 1 :
                              {
                                  cout<<"It is a simple sorting algorithm that repeatedly steps through the list to be sorted, compares each pair of adjacent items and swaps them if they are in the wrong order.Best case-O(n)Worst case-O(n^2)Average case-O(n^2)"<<endl;
                                   goto A;
                                   break;
                              }
                          case 2 :
                              {
                                  cout<<"compare 1st and 2nd elements\nif 1st larger than 2nd, swap\ncompare 2nd and 3rd, and swap if necessary\ncontinue until compare the last two elements\nthe largest element is now the last element in the array.\nrepeat statring from the beginning until no swaps are performed (i.e.,\nthe array is sorted)\neach time you go through the elements bubbling up the largest element\nno need to try the last i elements for the ith run since the end\nelements are already sorted"<<endl;
                                  goto A;
                                  break;
                              }
                          case 3 :
                              {
                                  cout<<"\nEnter the limit of your array :"<<endl;
                                  cin>>n;
                                  cout<<"\nEnter the elements of your array :"<<endl;
                                  for(a=0;a<n;a++)
                                  {
                                      cin>>arr[a];
                                  }
                                 bubbleSort(arr,n);
                                 goto A;
                                 break;
                              }
                        }
                         goto A;
                         break;
                    }
                    case 4:
                    {
                        cout<<"\nWhat would you like to choose :\n1.DESCRIPTION \n2.ALGORITHM\n3.EXAMPLE\n"<<endl;
                        cin>>y;

                        switch(y)
                        {
                          case 1 :
                              {
                                  cout<<"It is an efficient sorting algorithm, serving as a systematic method for placing the elements of an array in order.\nBest case-O(nlogn)\nWorst case-O(n)\nAverage case-O(nlogn)"<<endl;
                                   goto A;
                                   break;
                              }
                          case 2 :
                              {
                                  cout<<"If the number of elements in S is 0 or 1, return\npick any element in v in S. This is called the pivot.\nPartition the elements in S into two groups, those below the pivot\n(numerically) and those above the pivot.\nreturn quicksort of s1 followed by v followed by quicksort of s2"<<endl;
                                  goto A;
                                  break;
                              }
                          case 3 :
                              {
                                  cout<<"\nEnter the limit of your array :"<<endl;
                                  cin>>n;
                                  cout<<"\nEnter the elements of your array :"<<endl;
                                  for(a=0;a<n;a++)
                                  {
                                      cin>>arr[a];
                                  }
                                  cout<<"ENTER low"<<endl;
                                  cin>>low;
                                  cout<<"ENTER high"<<endl;
                                  cin>>high;
                                  quickSort(arr,low, high);
                                  goto A;

                                 break;
                              }
                        }
                         goto A;
                         break;
                    }
                    case 5:
                    {
                        cout<<"\nWhat would you like to choose : \n1.DESCRIPTION \n2.ALGORITHM\n3.EXAMPLE\n"<<endl;
                        cin>>y;

                        switch(y)
                        {
                          case 1 :
                              {
                                  cout<<"Count sort:It is an algorithm for sorting a collection of objects according to keys that are small integers that is, it is an integer sorting algorithm.\nBest case-O(n+k)\nWorst case-O(n+k)\nAverage case-O(n+k)"<<endl;
                                   goto A;
                                   break;
                              }
                          case 2 :
                              {
                                  cout<<"Allocate an array numCounts where the indices represent numbers from our input array and the values represent how many times the index number appears. Start each value at 0.\nIn one pass of the input array, update numCounts as you go, so that at the end the values in numCounts are correct.\nAllocate an array sortedArray where we'll store our sorted numbers.\nIn one in-order pass of numCounts put each number, the correct number of times, into sortedArray."<<endl;
                                  goto A;
                                  break;
                              }
                          case 3 :
                              {
                                 cout<<"\nEnter the limit of your array :"<<endl;
                                  cin>>n;
                                  cout<<"\nEnter the elements of your array :"<<endl;
                                  for(a=0;a<n;a++)
                                  {
                                      cin>>arr[a];
                                  }
                                 cSort(arr,n);
                                 goto A;
                                 break;
                              }
                        }
                         goto A;
                         break;
                    }
                    case 6:
                    {
                        cout<<"\nWhat would you like to choose : \n1.DESCRIPTION \n2.ALGORITHM\n3.EXAMPLE\n"<<endl;
                        cin>>y;

                        switch(y)
                        {
                          case 1 :
                              {
                                  cout<<"It is a non-comparative integer sorting algorithm that sorts data with integer keys by grouping keys by the individual digits which share the same significant position and value.\nBest case-O(nk)\nWorst case-O(nk)\nAverage case-O(nk)"<<endl;
                                   goto A;
                                   break;
                              }
                          case 2 :
                              {
                                  cout<<"For each digit i where i varies from the least significant digit to the most significant digit of a numberSort input array using countsort algorithm according to ith digit.\nWe used count sort because it is a stable sort."<<endl;
                                  goto A;
                                  break;
                              }
                          case 3 :
                              {
                                  cout<<"\nEnter the limit of your array :"<<endl;
                                  cin>>n;
                                  cout<<"\nEnter the elements of your array :"<<endl;
                                  for(a=0;a<n;a++)
                                  {
                                      cin>>arr[a];
                                  }

                                  radixsort(arr, n);
                                 goto A;
                                 break;
                              }
                        }
                         goto A;
                         break;
                    }
                    case 7:
                    {
                        cout<<"\nWhat would you like to choose :\n1.DESCRIPTION \n2.ALGORITHM\n3.EXAMPLE\n"<<endl;
                        cin>>y;

                        switch(y)
                        {
                          case 1 :
                              {
                                  cout<<"Bucket sort:Bucket sort is mainly useful when input is uniformly distributed over a range.\nBest case-O(nk)\nWorst case-O(n^2)\nAverage case-O(nk)"<<endl;
                                   goto A;
                                   break;
                              }
                          case 2 :
                              {
                                  cout<<"array of the size of maximum element + 1\ncounts the number of elements of each\nuseful where input is only small integers"<<endl;
                                  goto A;
                                  break;
                              }
                          case 3 :
                              {
                                  cout<<"\nEnter the limit of your array :"<<endl;
                                  cin>>n;
                                  cout<<"\nEnter the elements of your array :"<<endl;
                                  for(a=0;a<n;a++)
                                  {
                                      cin>>arr[a];
                                  }
                                  bucketSort(arr, n);
                                 goto A;
                                 break;
                              }
                        }
                        goto A;
                         break;
                    }
                    case 8:
                    {
                        cout<<"\nWhat would you like to choose :\n1.DESCRIPTION \n2.ALGORITHM\n3.EXAMPLE\n"<<endl;
                        cin>>y;

                        switch(y)
                        {
                          case 1 :
                              {
                                  cout<<"It divides input array in two halves, calls itself for the two halves and then merges the two sorted halves.\nBest case-O(nlogn)\nWorst case-O(nlogn)\nAverage case-O(nlogn)"<<endl;
                                   goto A;
                                   break;
                              }
                          case 2 :
                              {
                                  cout<<"mergesort mergeRecursively merges two sorted lists\nTime to merge two sorted lists is linear (N-1 comparisons)\n1 13 24 26 merge 2 15 27 38 gives 1 2 13 15 24 26 27 38\nClassic Divide and Conquer Strategy\nIf more than one element, divide and merge sort the first and secondhalf"<<endl;
                                  goto A;
                                  break;
                              }
                          case 3 :
                              {
                                  cout<<"\nEnter the leftmost of your array :"<<endl;
                                  cin>>l;
                                   cout<<"\nEnter the rightmost of your array :"<<endl;
                                  cin>>r;
                                  cout<<"\nEnter the elements of your array :"<<endl;
                                  for(a=0;a<n;a++)
                                  {
                                      cin>>arr[a];
                                  }
                                  mergeSort(arr, l,  r);
                                 goto A;
                                 break;
                              }
                        }
                         goto A;
                         break;
                    }
                          default:
                            goto A;
                }
            }
             case 2 :
            {
               cout<<"\n\nFROM THE GIVEN MENU PICK YOUR CHOICE :\n1.LINEAR SEARCH \n2.BINARY SEARCH \n3. INTERPOLATION SEARCH\n"<<endl;
                cin>>z;
                switch(z)
                {
                    case 1 :
                        {
                            cout<<"\nWhat would you like to choose :\n1.DESCRIPTION \n2.ALGORITHM\n3.EXAMPLE\n"<<endl;
                            cin>>y;

                            switch(y)
                            {
                                case 1 :
                                {
                                  cout<<"It sequentially checks each element of the list for the target value until a match is found or until all the elements have been searched.\nBest case-O(1)\nAverage case-O(n)\nWorst case-O(n)"<<endl;
                                  goto A;
                                }
                                case 2 :
                                {
                                  cout<<"Linear Search ( Array A, Value x)\nStep 1: Set i to 1\nStep 2: if i > n then go to step 7\nStep 3: if A[i] = x then go to step 6\nStep 4: Set i to i + 1\nStep 5: Go to Step 2\nStep 6: Print Element x Found at index i and go to step 8\nStep 7: Print element not found\nStep 8: Exit"<<endl;
                                  goto A;
                                }
                                case 3 :
                                {
                                    cout<<"\nEnter the limit of your array :"<<endl;
                                  cin>>n;
                                  cout<<"\nEnter the elements of your array :"<<endl;
                                  for(a=0;a<n;a++)
                                  {
                                      cin>>arr[a];
                                  }
                                  cout<<"\nEnter the element that is to be found :"<<endl;
                                  cin>>x;

                                 position= search(arr,n,x);
                                 cout<<position;
                                 goto A;
                                }
                            goto A;
                            break;
                           }
                        }
                         case 2:
                        {
                            cout<<"\nWhat would you like to choose :\n1.DESCRIPTION \n2.ALGORITHM\n3.EXAMPLE\n"<<endl;
                            cin>>y;

                            switch(y)
                            {
                                case 1 :
                                {
                                    cout<<"It is a search algorithm that finds the position of a target value within a sorted array.\nBest case-O(1)\nAverage case-O(logn)\nWorst case-O(logn)"<<endl;
                                  goto A;
                                  break;
                                }
                                case 2 :
                                {
                                    cout<<"Given an array A of n elements with values or records A0, A1, ..., An−1, sorted such that A0 ≤ A1 ≤ ... ≤ An−1, and target value T, the following subroutine uses binary search to find the index of T in A.[7]\nSet L to 0 and R to n − 1.\nIf L > R, the search terminates as unsuccessful.\nSet m (the position of the middle element) to the floor (the largest previous integer) of (L + R) / 2.\nIf Am < T, set L to m + 1 and go to step 2.\nIf Am > T, set R to m − 1 and go to step 2.\nNow Am = T, the search is done; return m."<<endl;
                                   goto A;
                                   break;
                                }
                                case 3 :
                                {

                                    cout<<"\nEnter the element that is to be found :"<<endl;
                                    cin>>x;
                                     cout<<"\nEnter the limit of your array :"<<endl;
                                  cin>>n;
                                  cout<<"\nEnter the elements of your array :"<<endl;
                                  for(a=0;a<n;a++)
                                  {
                                      cin>>arr[a];
                                  }
                                  cout<<"ENTER low"<<endl;
                                  cin>>low;
                                  cout<<"ENTER high"<<endl;
                                  cin>>high;
                                  position=binarySearch(arr,low, high, x);
                                  cout<<position;
                                    goto A;
                                    break;
                                }
                                goto A;
                            break;
                           }
                        }

                    case 3:
                        {
                            cout<<"\nWhat would you like to choose :\n1.DESCRIPTION \n2.ALGORITHM\n3.EXAMPLE\n"<<endl;
                            cin>>y;

                            switch(y)
                            {
                                case 1 :
                                {
                                    cout<<"It parallels how humans search through a telephone book for a particular name, the key value by which the book's entries are ordered.\nBest case-O(1)\nAverage case-O(loglogn)\nWorst case-O(n)"<<endl;
                                   goto A;
                                   break;
                                }
                                case 2 :
                                {
                                    cout<<"Rest of the Interpolation algorithm is same except the above partition logic.\nStep1: In a loop, calculate the value of “pos” using the probe position formula.\nStep2: If it is a match, return the index of the item, and exit.\nStep3: If the item is less than arr[pos], calculate the probe position of the left sub-array. Otherwise calculate the same in the right sub-array.\nStep4: Repeat until a match is found or the sub-array reduces to zero."<<endl;
                                   goto A;
                                   break;
                                }
                                case 3 :
                                {
                                     cout<<"\nEnter the element that is to be found :"<<endl;
                                    cin>>x;
                                     cout<<"\nEnter the limit of your array :"<<endl;
                                  cin>>n;
                                  cout<<"\nEnter the elements of your array :"<<endl;
                                  for(a=0;a<n;a++)
                                  {
                                      cin>>arr[a];
                                  }
                                  position=interpolationSearch(arr,  n, x);
                                  cout<<position;
                                     goto A;
                                     break;
                                }
                            goto A;
                            break;
                           }
                        }
                                default:
                                    goto A;
                        }
    }
    case 3:
    {
        int linearSearchComp=0;
	    int binarySearchComp=0;
	    int insertionSortComp=0;
	    int selectionSortComp=0;
	    int bubbleSortComp=0;
	    int mergeSortComp=0;

	for(int i = 0; i < 50; i++) //runs 50 instances of the various sorting and seraching methods on data
	{
		SearchAndSort arr;
		cout << "Initial Conditions" << endl;
		arr.print();

		cout << endl << "After Linear Search" << endl;
		linearSearchComp = linearSearchComp + arr.linearSearch(50);
		arr.print();

		cout << endl << "After Binary Search" << endl;
		binarySearchComp = binarySearchComp + arr.binarySearch(50);
		arr.print();

		cout << endl << "After Insertion Sort" << endl;
		insertionSortComp = insertionSortComp + arr.insertionSort();
		arr.print();

		cout << endl << "After Selection Sort" << endl;
		selectionSortComp = selectionSortComp + arr.selectionSort();
		arr.print();

		cout << endl << "After Bubble Sort" << endl;
		bubbleSortComp = bubbleSortComp + arr.bubbleSort();
		arr.print();

		cout << endl << "After Merge Sort" << endl;
		mergeSortComp = mergeSortComp + arr.mergeSort();
		arr.print();
	}

	//detemines the average amount of comparisons for that are used for each searching and sorting algorithms
	linearSearchComp = linearSearchComp / 50;
	binarySearchComp = binarySearchComp / 50;
	insertionSortComp = insertionSortComp / 50;
	selectionSortComp = selectionSortComp / 50;
	bubbleSortComp = bubbleSortComp / 50;
	mergeSortComp = mergeSortComp / 50;

	//outputs the averge number of comparisons performed for each searching and sorting algorithms
	cout << "Average Number of Comparisons for Linear Search " << linearSearchComp << endl;
	cout << "Average Number of Comparisons for Binary Search " << binarySearchComp << endl;
	cout << "Average Number of Comparisons for Insertion Sort " << insertionSortComp << endl;
	cout << "Average Number of Comparisons for Selection Sort " << selectionSortComp << endl;
	cout << "Average Number of Comparisons for Bubble Sort " << bubbleSortComp << endl;
	cout << "Average Number of Comparisons for Merge Sort " << mergeSortComp << endl;
    goto A;
	system("pause");
     }

    }
    goto A;

           }
    cout<<"\n\t\t\tTHANKS FOR USING PROJECT \t\n\n ";


    }}




int main()
{
   system(" color 0A");
   cout<<" \n____________________________________________________________________________________________________\n\n";
   cout<<" \n____________________________________Fun with DATA STRUCTURES________________________________________\n\n";
   cout<<" \n____________________________________________________________________________________________________\n\n";
   cout<<" \n__________________Guided by________________________________________________________Made by__________\n\n";
   cout<<" \n_________________Ashish Sir__________________________________________________Divik Shrivastava,_____\n\n";
   cout<<" \n_______________________________________________________________________________Priya Vajpeyi________\n\n";
   calc obj;
   obj.in();
   obj.ans();

   return 0;
}
