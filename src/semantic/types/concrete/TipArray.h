#pragma once

#include "TipCons.h"
#include "TipType.h"
#include "string"
#include "vector"


/*!
 * \class TipArray
 *
 * \brief A proper type representing an array
 */

class TipArray : public TipCons {
public:
  TipArray() = delete;
  TipArray(std::shared_ptr<TipType> of);

  std::shared_ptr<TipType> getAddressOfField() const;

  bool operator==(const TipType &other) const override;
  bool operator!=(const TipType &other) const override;

  void accept(TipTypeVisitor *visitor) override;

protected:
  std::ostream &print(std::ostream &out) const override;
};
