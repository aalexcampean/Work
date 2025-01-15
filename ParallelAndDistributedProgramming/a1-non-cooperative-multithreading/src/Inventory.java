import java.util.HashMap;
import java.util.Set;

public class Inventory {
    private HashMap<Product, Integer> products;

    public Inventory() {
        this.products = new HashMap<>();
    }

    public Inventory(HashMap<Product, Integer> products) {
        this.products = products;
    }

    public Set<Product> getProducts() {
        return this.products.keySet();
    }

    public Integer getProductQuantity(Product product) {
        return this.products.getOrDefault(product, 0);
    }

    public Double computeTotalSum() {
        return products.keySet().stream()
                .mapToDouble(product -> getProductQuantity(product) * product.getPrice())
                .sum();
    }

    public void add(Product product, Integer quantity) {
        this.products.put(product, quantity);
    }

    public void remove(Product product, Integer quantity) {
        if (!this.products.containsKey(product))
            throw new RuntimeException("Nonexistent specified product");

        if (this.getProductQuantity(product) < quantity)
            throw new RuntimeException("Insufficient quantity for specified product");

        int newQuantity = this.getProductQuantity(product) - quantity;

        if (newQuantity == 0)
            this.products.remove(product);
        else
            this.products.put(product, newQuantity);
    }

    @Override
    public String toString() {
        StringBuilder stringBuilder = new StringBuilder();
        this.products.forEach((product, quantity) -> {
            stringBuilder.append(product.getName()).append(", Quantity: ");
            stringBuilder.append(quantity).append("\n");
        });
        return stringBuilder.toString();
    }
}
