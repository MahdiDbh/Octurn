#pragma once
#include <cstddef>
#include <cstdint>
#include <optional>
#include <string>
#include <unordered_map>
#include <vector>

#include "types/types.hpp"
#include "equity/equity.hpp"
#include "marketTypes/marketTypes.hpp"
#include "injector/DataInjector.hpp"
#include "src/apiConnector.hpp"

class DataLayer {
private:
    DataInjector injector_;
    Octurn::EquityMap equityMap_;
    std::vector<uint64_t> masterTimestamps_;

    const Equity& equity(const std::string& ticker) const;
    const std::vector<double>& series(const std::string& ticker, const std::string& field) const;
    const std::vector<double>& seriesByName(const std::string& seriesName) const;

public:
    static std::string makeField(const std::string& ticker, const std::string& field);

    DataLayer(const std::string& APIKEY, const std::string& source, const connector& connector);

    void extract(const std::vector<connector>& requests);
    const Octurn::EquityMap& equities() const;
    Bar getBar(const std::string& ticker, size_t idx) const;
    double getValue(const std::string& key, size_t idx) const;
    void masterTimestamps();
    std::optional<size_t> indexFor(const std::string& ticker, uint64_t ts) const;
};
