class TableCell {
public:
    virtual std::string get_data() = 0;
};

class IntegerTableCell : public TableCell{
public:
    explicit IntegerTableCell(int data){
        data_ = data;
    }

    std::string get_data() override{
        return std::to_string(data_);
    }

private:
    int data_;
};

class TableRow{
public:
    explicit TableRow(std::vector<std::shared_ptr<TableCell>> cells){
        cells_ = std::move(cells);
    }

    std::string get_cell(size_t number){
        return cells_[number]->get_data();
    }

    std::string to_string();

private:
    std::vector<std::shared_ptr<TableCell>> cells_;
};