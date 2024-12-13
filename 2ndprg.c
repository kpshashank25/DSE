import time
import csv
from selenium import webdriver
from selenium.webdriver.chrome.service import Service
from selenium.webdriver.chrome.options import Options
from selenium.webdriver.common.by import By
from selenium.webdriver.common.keys import Keys
from selenium.webdriver.common.action_chains import ActionChains
from selenium.webdriver.support.ui import WebDriverWait
from selenium.webdriver.support import expected_conditions as EC
from webdriver_manager.chrome import ChromeDriverManager

def fetch_flat_apartment_prices_to_csv():
    try:
        # Setup Chrome options
        options = Options()
        options.add_argument("--start-maximized")  # Start browser maximized
        service = Service(ChromeDriverManager().install())  # Auto-manage driver
        driver = webdriver.Chrome(service=service, options=options)

        # Open Housing.com
        driver.get('https://housing.com/')
        WebDriverWait(driver, 10).until(
            EC.presence_of_element_located((By.CLASS_NAME, "css-1s4ak33"))
        )

        # Search for Bangalore
        search_box = driver.find_element(By.CLASS_NAME, "css-1s4ak33")
        ActionChains(driver).click(search_box).send_keys("Bangalore").send_keys(Keys.RETURN).perform()
        print("Typing 'Bangalore' and pressing Enter...")
        time.sleep(5)  # Wait for results to load

        # Open CSV file to save data
        with open('property_listings.csv', mode='w', newline='', encoding='utf-8') as file:
            writer = csv.writer(file)
            writer.writerow(["Location", "Price"])  # Header row

            # Extract property details
            count = 0
            while count < 10:  # Limit to the first 10 entries
                try:
                    # Refined XPath for price and location
                    price_xpath = f"//*[@id='srp-{count + 1}']/div[1]/div[2]/div[1]/div[1]/div[1]/div"
                    location_xpath = f"//*[@id='srp-{count + 1}']/div[1]/div[2]/div[1]/h3/span"

                    # Wait for elements to load
                    price_element = WebDriverWait(driver, 10).until(
                        EC.presence_of_element_located((By.XPATH, price_xpath))
                    )
                    location_element = WebDriverWait(driver, 10).until(
                        EC.presence_of_element_located((By.XPATH, location_xpath))
                    )

                    # Extract text
                    price = price_element.text
                    location = location_element.text

                    # Write to CSV
                    print(f"Location: {location}, Price: {price}")
                    writer.writerow([location, price])
                    count += 1

                except Exception as e:
                    print(f"Error extracting property details for entry {count + 1}: {e}")
                    break

        print("Property listings saved to 'property_listings.csv'.")

    except Exception as e:
        print(f"An error occurred: {e}")

    finally:
        driver.quit()

# Run the function
fetch_flat_apartment_prices_to_csv()










