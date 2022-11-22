//
// Created by Alex Campean on 06.04.2022.
//

#include "../Domain/Bill.h"
#include <vector>

class Repository {
private:
    std::vector<Bill> bills;
public:
    Repository();
    ~Repository();

    /// Getters
    int getRepositorySize() const;
    std::vector<Bill> getAllBills() const;

    /// Add, Delete Bill
    void addBill(const Bill &bill);
    ///<summary>Deletes an existing bill from the Repository based on its SerialNumber</summary>
    ///<param name="inputSerialNumber">std::String the SerialNUmber of the Bill to be deleted</param>
    ///<returns></returns>
    void deleteBill(const std::string &inputSerialNumber);

    /// Operator Overload
    Bill& operator[](int index);
    friend std::ostream& operator<<(std::ostream& out, const Repository& repository);
};
inline std::ostream& operator<<(std::ostream& out, const Repository& repository) {
    std::for_each(repository.bills.begin(), repository.bills.end(), [&out](auto &it){
        out << it << "\n";
    });
    return out;
}


