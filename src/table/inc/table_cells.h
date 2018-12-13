#pragma once

#include <string>
#include <vector>
#include <memory>

namespace st_e {

class TableCell {
public:
    virtual ~TableCell() = default;
    virtual std::string get_data() = 0;
    // resizes vector and ads binary representation to it
    virtual void push_into_buffer(std::vector<char>& buffer) const = 0;
    virtual void set_value(std::string) = 0;
};

class IntegerTableCell : public TableCell {
public:
    explicit IntegerTableCell(int32_t data) : data_(data) {}
    std::string get_data() override { return std::to_string(data_); }
    // todo: maybe do like this?
    void push_into_buffer(std::vector<char>& buffer) const override;
    void set_value(std::string value) override;

private:
    int32_t data_;
};

class BoolTableCell : public TableCell {
public:
    explicit BoolTableCell(bool data) : data_(data) {}
    std::string get_data() override;
    // todo: maybe do like this?
    void push_into_buffer(std::vector<char>& buffer) const override;
    void set_value(std::string value) override;

private:
    bool data_;
};

class VarCharTableCell : public TableCell {
public:
    explicit VarCharTableCell(std::string data) : data_(std::move(data)) {}
    std::string get_data() override { return data_; }
    // todo: maybe do like this?
    void push_into_buffer(std::vector<char>& buffer) const override;
    void set_value(std::string value) override;

private:
    std::string data_;
};

class TableRow {
public:
    using ArrayOfCells = std::vector<std::shared_ptr<st_e::TableCell>>;

    explicit TableRow(ArrayOfCells cells, bool is_deleted) : cells_(std::move(cells)), is_removed_(is_deleted) {}

//    std::string get_cell(size_t number){ return cells_[number].get_data(); }
    const ArrayOfCells& get_cells() const { return cells_; }
    bool is_removed() const { return is_removed_; }
    void remove() { is_removed_ = true; }
    void push_binary(std::vector<char>& input) const;

private:
    ArrayOfCells cells_;
    bool is_removed_ = false;
};


} // namespace st_e