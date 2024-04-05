import requests
import json

def stress_test(json_data):
    url = "https://fcsbalancer.foresth11projects.com/customer_request"
    # url = "http://localhost:8080/junk"
    headers = {'Content-Type': 'application/json'}

    try:
        response = requests.post(url, headers=headers, json=json_data)
        if response.status_code == 200:
            print("Request successful:", response.text)
        else:
            print("Request failed with status code:", response.status_code)
    except Exception as e:
        print("An error occurred:", e)

# Example JSON data
# json_array = json.dumps(["Apples"])
product_list_set = {"Apples",
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
    "Granola"}
grocery_list = []
while True:
    print("\nEnter a grocery item\n\nType 'check' to list available items\n\nType 'q' to finish adding items")
    x = input()
    match x:
        case 'q':
            break
        case 'check':
            print(product_list_set)
            continue
    if x in product_list_set:
        grocery_list.append(x)
    else:
        print("\n\nPlease choose an item we have in stock, type 'check' to see a list\n\n")
        
print(grocery_list)

stress_test(grocery_list)
