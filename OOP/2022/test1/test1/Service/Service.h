//
// Created by Alex Campean on 06.04.2022.
//

#include "../Repository/Repository.h"


class Service {
private:
    Repository* repository;
public:
    Service();
    Service(Repository *inputRepository);
    ~Service();

    /// Getters
    int getServiceSize() const;
    std::vector<Bill> getAllService() const;
    std::vector<Bill> getAllPaidBillsSortedByDueDate() const;
    std::vector<Bill> getAllUnpaidBills() const;

    /// Add, Delete Bill
    void addBillService(const std::string &inputSerialNumber, const std::string &inputCompany, int inputDay, int inputMonth,
                        int inputYear, double inputSum, bool inputIsPaid);
    ///<summary>Deletes an existing bill from the Service based on its SerialNumber</summary>
    ///<param name="inputSerialNumber">std::String the SerialNUmber of the Bill to be deleted</param>
    ///<returns></returns>
    void deleteBillService(const std::string &inputSerialNumber);

    /// Compute Total
    double computeTotalSumForUnpaidBills();

    /// Initial Entries
    void addInitialEntries();
};


