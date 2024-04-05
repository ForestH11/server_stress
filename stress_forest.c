#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>
#include <uuid/uuid.h>
#include <time.h>
#include <limits.h>
#include <pthread.h>


// To complile: gcc -o stresser stresser.c -lcurl -lpthread  

/**
 * @brief Adds a new HTTP POST request to the curl multi handle with specified options.
 *
 * This function initializes a curl easy handle, sets up the full URL by concatenating
 * `serverUrl` and `endpoint`, and configures the request type as POST with the provided
 * data and headers. The configured request is then added to the specified curl multi handle.
 *
 * @param cm Pointer to the CURLM multi handle to which the request will be added.
 * @param serverUrl The base URL of the server to which the request is made.
 * @param endpoint The specific endpoint at the server to which the request is made.
 * @param data The data to be posted in the request body.
 * @param headers Pointer to a curl_slist struct containing the headers to be included in the request.
 *
 * @note The function assumes `cm` and `eh` have been properly initialized and that
 *       `serverUrl`, `endpoint`, and `data` are null-terminated strings. The function
 *       does not take ownership of the provided pointers, and it's the caller's responsibility
 *       to manage their memory. Additionally, the caller must ensure that the `curl_slist`
 *       referenced by `headers` remains valid until the request is completed.
 *
 * @author Lee Barney
 * @version 1.0
 * @date 2024-03-18
 * @complexity O(1) - The function performs a constant number of operations regardless of input size.
 */
void add_request(CURLM *cm, const char* serverUrl, const char* endpoint, const char* data, struct curl_slist *headers) {
    CURL *eh = curl_easy_init();
    char fullUrl[256];

    if(eh) {
        snprintf(fullUrl, sizeof(fullUrl), "%s%s", serverUrl, endpoint);
        curl_easy_setopt(eh, CURLOPT_URL, fullUrl);
        curl_easy_setopt(eh, CURLOPT_POST, 1L);
        curl_easy_setopt(eh, CURLOPT_COPYPOSTFIELDS, data);
        curl_easy_setopt(eh, CURLOPT_HTTPHEADER, headers); // Use passed headers
        curl_multi_add_handle(cm, eh);
    }
}


char *generate_grocery_list(int size) {
    char *grocery_items[] = {
    "Apples",
    "Bananas",
    "Oranges",
    "Strawberries",
    "Grapes",
    "Lemons",
    "Limes",
    "Watermelon",
    "Pineapple",
    "Kiwi",
    "Blueberries",
    "Raspberries",
    "Mangoes",
    "Peaches",
    "Plums",
    "Avocado",
    "Tomatoes",
    "Cucumbers",
    "Bell Peppers",
    "Carrots",
    "Celery",
    "Lettuce",
    "Spinach",
    "Kale",
    "Potatoes",
    "Sweet Potatoes",
    "Onions",
    "Garlic",
    "Ginger",
    "Mushrooms",
    "Zucchini",
    "Broccoli",
    "Cauliflower",
    "Asparagus",
    "Green Beans",
    "Peas",
    "Corn",
    "Eggs",
    "Milk",
    "Butter",
    "Cheese",
    "Yogurt",
    "Bread",
    "Bagels",
    "Tortillas",
    "Pasta",
    "Rice",
    "Quinoa",
    "Oats",
    "Cereal",
    "Peanut Butter",
    "Jam",
    "Honey",
    "Maple Syrup",
    "Olive Oil",
    "Vegetable Oil",
    "Coconut Oil",
    "Vinegar",
    "Soy Sauce",
    "Teriyaki Sauce",
    "Ketchup",
    "Mustard",
    "Mayonnaise",
    "BBQ Sauce",
    "Salsa",
    "Guacamole",
    "Salad Dressing",
    "Canned Beans",
    "Canned Tomatoes",
    "Canned Corn",
    "Canned Tuna",
    "Canned Salmon",
    "Canned Soup",
    "Pasta Sauce",
    "Dried Beans",
    "Dried Lentils",
    "Dried Fruit",
    "Nuts",
    "Seeds",
    "Popcorn",
    "Chips",
    "Crackers",
    "Pretzels",
    "Chocolate",
    "Cookies",
    "Granola Bars",
    "Ice Cream",
    "Frozen Vegetables",
    "Frozen Fruits",
    "Frozen Pizza",
    "Frozen Meals",
    "Frozen Desserts",
    "Frozen Burritos",
    "Frozen Chicken Nuggets",
    "Frozen French Fries",
    "Frozen Fish Fillets",
    "Frozen Shrimp",
    "Frozen Breakfast Sandwiches",
    "Frozen Waffles",
    "Granola"
};
    char *json_list = malloc((size * 20 + 10) * sizeof(char)); // Allocate memory for JSON string
    strcpy(json_list, "[");
    for (int i = 0; i < size; i++) {
        strcat(json_list, "\"");
        strcat(json_list, grocery_items[rand() % 8]);
        strcat(json_list, "\",");
        // strcat(json_list, ",");
        // printf("in for loop %s\n\n", json_list);
    }
    strcat(json_list, "]");
    // json_list = "[Apples]";
    // printf("json_list is %s\n",json_list);
    return json_list;
}

/**
 * @brief Sends a series of asynchronous HTTP requests for package management, including
 * package transfers, location requests, location updates, and delivery notifications.
 * 
 * This function orchestrates a sequence of HTTP operations to simulate various stages in
 * the package delivery process. It employs the libcurl multi interface to handle HTTP
 * requests asynchronously, ensuring efficient network communication. Additionally, the
 * function uses the libuuid library to generate unique identifiers for packages and their
 * respective locations, essential for tracking and management purposes. Memory for thread
 * arguments is dynamically allocated, emphasizing the need for careful resource management
 * and cleanup to prevent memory leaks. The procedure covers transferring packages, fetching
 * location information, updating locations based on predefined intervals, and marking packages
 * as delivered, demonstrating a comprehensive approach to package handling and delivery simulation.
 * 
 * @param arg A void pointer to an array of arguments that include the server URL, the total
 * number of packages to process, the number of requests per package type, and the frequency of
 * location updates per location change. This design allows for flexible adaptation to varying
 * operational requirements and scenarios.
 * 
 * @return Always returns NULL. The function is tailored for threading scenarios, where it may
 * serve as a worker routine. The NULL return value signifies completion without the need for
 * outputting specific results, aligning with common threading paradigms.
 * 
 * @author Lee Barney
 * @version 1.1
 * @date 2024-03-29
 * @complexity O(n*m*k) where n is the number of packages, m represents the requests per package type,
 * and k signifies the location updates per location change. This complexity notation reflects the
 * nested operational loops, encapsulating the multi-layered process flow encompassing package
 * transfers, location requests/updates, and delivery confirmations.
 */
void* sendMessages(void* arg){

    char** argv = (char**)arg;
    int requestCount = atoi(argv[2]);
    int listSize = atoi(argv[3]);
    const char* serverUrl = argv[4];
    // printf("request count: %d\nlist size: %d\nserver url: %s\n",requestCount,listSize,serverUrl);

    CURLM *cm;
    int still_running = 0;

    curl_global_init(CURL_GLOBAL_ALL);
    cm = curl_multi_init();

    struct curl_slist *headers = NULL;
    headers = curl_slist_append(headers, "Content-Type: application/json");

    srandom((unsigned int)time(NULL));
    for (int i = 0; i < requestCount; i++) {

        //generate random grocery list
        char* payload = generate_grocery_list(listSize);
        // printf("Payload is %s\n", payload);

        char data[1024];//max size of the data string to be sent

            // // Package Location Request
            snprintf(data, sizeof(data), "%s", payload);
            add_request(cm, serverUrl, "/customer_request", data, headers);
            // printf("Adding JSON: %s\n", data);
        
    curl_multi_perform(cm, &still_running);

        while (still_running) {
            fd_set fdread;
            fd_set fdwrite;
            fd_set fdexcep;
            int maxfd = -1;
            struct timeval timeout;
            long curl_timeo = -1;

            FD_ZERO(&fdread);
            FD_ZERO(&fdwrite);
            FD_ZERO(&fdexcep);

            timeout.tv_sec = 1;
            timeout.tv_usec = 0;

            curl_multi_timeout(cm, &curl_timeo);
            if (curl_timeo >= 0) {
                timeout.tv_sec = curl_timeo / 1000;
                if (timeout.tv_sec > 1)
                    timeout.tv_sec = 1;
                else
                    timeout.tv_usec = (curl_timeo % 1000) * 1000;
            }

            curl_multi_fdset(cm, &fdread, &fdwrite, &fdexcep, &maxfd);

            if (maxfd == -1) {
                struct timespec wait = {0, 100 * 1000000}; // 100ms
                nanosleep(&wait, NULL);
            } else {
                select(maxfd + 1, &fdread, &fdwrite, &fdexcep, &timeout);
            }

            curl_multi_perform(cm, &still_running);
        }

    }

    // Cleanup
    CURLMsg *msg;
    int msgs_left;
    CURL *easy;
    CURLcode res;

    while ((msg = curl_multi_info_read(cm, &msgs_left))) {
        if (msg->msg == CURLMSG_DONE) {
            easy = msg->easy_handle;
            res = msg->data.result;
            curl_multi_remove_handle(cm, easy);
            curl_easy_cleanup(easy);
        }
    }

    curl_multi_cleanup(cm);
    curl_slist_free_all(headers); // Free headers after all requests are complete
    curl_global_cleanup();

    return NULL;
}
/**
 * @brief Entry point for a multithreaded application designed to perform stress testing
 * on a server by simulating package management operations.
 * 
 * This program initiates a specified number of threads to send asynchronous HTTP requests
 * to a server, emulating a series of package transfers and location updates. Each thread
 * performs operations based on the provided command-line arguments, which define the scale
 * and scope of the test, including the number of packages, package transfers per package,
 * and location changes per package transfer. The program validates input arguments, manages
 * thread creation and synchronization, calculates the duration of the operation, and ensures
 * proper cleanup of allocated resources. It demonstrates effective multithreading and resource
 * management practices in a C environment, as well as error handling and user feedback.
 *
 * Usage:
 * The program requires 5 command-line arguments specifying the operational parameters:
 * 1. Number of Threads
 * 2. Number of Packages
 * 3. Number of Package Transfers for Each Package
 * 4. Number of Location Changes for each Package Transfer
 * 5. Server domain (e.g., your.domain.ext)
 * 
 * @param argc The count of command-line arguments.
 * @param argv An array of command-line argument strings.
 * 
 * @return Returns 0 on successful completion or 1 if there's an error or incorrect usage.
 * 
 * @note The total number of messages sent is (Number of Threads) * (Number of Packages) * (Number of Transfers) * (Number of Location Changes) 
 * 
 * @author Lee Barney
 * @version 1.1
 * @date 2024-03-29
 * @complexity O(n) where n is the number of threads. The complexity mainly arises from
 * the creation and joining of threads, as each thread is handled independently.
 */

int main(int argc, char **argv) {
    if (argc != 5) {
        fprintf(stderr, "Usage: %s <Number of Threads> <Number of Requests> <List_size> <your.domain.ext>\n", argv[0]);
        return 1;
    }

    int threadCount = atoi(argv[1]);
    pthread_t* threads = malloc(threadCount * sizeof(pthread_t));//allocate memory for the threads
    if (!threads) {
        fprintf(stderr, "Failed to allocate memory for threads\n");
        return 1;
    }

    /*
     * Create and start the threads to sent the stresser messages
     */

    time_t startTime = time(NULL);
    for (int i = 0; i < threadCount; ++i) {
        if (pthread_create(&threads[i], NULL, sendMessages, argv)) {
            fprintf(stderr, "Error creating thread %d\n", i + 1);
            free(threads);
            return 1;
        }
    }

    // Wait for the threads to finish
    for (int i = 0; i < threadCount; ++i) {
        pthread_join(threads[i], NULL);
    }

    time_t endTime = time(NULL);
    printf("Total duration for all messages: %ld seconds\n", endTime - startTime);
    fflush(stdout);

    free(threads);
    return 0;


}
