#ifndef FINANCIAL_MARKET_HXX_
#define FINANCIAL_MARKET_HXX_

#include "Way.h"
#include "GenericOrder.h"

#include "OrderFactory.h"
#include "FinancialMarket.h"

template <typename InstrumentType, typename OrderTraits, typename InstrumentTraits>
void FinancialMarket<InstrumentType, OrderTraits, InstrumentTraits>::LoadReferential()
{
	// unique id, name, isin, mnemo
	typedef std::tuple<typename InstrumentTraits::InstrumentIDType, const std::string, const std::string, const std::string> TupleType;
	std::vector<TupleType> listing;

	listing.emplace_back(TupleType(0, "ACCOR", "FR0000120404", "AC"));
	listing.emplace_back(TupleType(1, "TOTAL", "FR0000120271", "FP"));

	for (const auto& tuple : listing)
	{
		std::shared_ptr<InstrumentType> instrument(new typename InstrumentType(std::get<0>(tuple), std::get<1>(tuple), std::get<2>(tuple), std::get<3>(tuple)));
		matchingEngine_.CreateOrderBook(instrument->GetInstrumentID());
		referential_.AddInstrument(std::move(instrument));
	}

	//referential_.TestProtobuf();
}

template <typename InstrumentType, typename OrderTraits, typename InstrumentTraits>
void FinancialMarket<InstrumentType, OrderTraits, InstrumentTraits>::TestAddOrder()
{
    auto order = OrderFactory::BuildOrder<GenericOrder<typename OrderTraits, typename InstrumentTraits>>(0, Way::BUY, 10, 15); 
    matchingEngine_.AddOrder(std::move(order));
}


#endif