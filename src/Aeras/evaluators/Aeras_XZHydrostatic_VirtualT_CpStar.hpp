//*****************************************************************//
//    Albany 2.0:  Copyright 2012 Sandia Corporation               //
//    This Software is released under the BSD license detailed     //
//    in the file "license.txt" in the top-level Albany directory  //
//*****************************************************************//

#ifndef AERAS_XZHYDROSTATIC_VIRTUALT_CPSTAR_HPP
#define AERAS_XZHYDROSTATIC_VIRTUALT_CPSTAR_HPP

#include "Phalanx_ConfigDefs.hpp"
#include "Phalanx_Evaluator_WithBaseImpl.hpp"
#include "Phalanx_Evaluator_Derived.hpp"
#include "Phalanx_MDField.hpp"
#include "Aeras_Layouts.hpp"

namespace Aeras {
/** \brief Virtual Temperature and Cp* for XZHydrostatic atmospheric model

    This evaluator computes the virtual temperature and Cp* 
    for the XZHydrostatic model of atmospheric dynamics.
    Tv = T + (Rv/R -1)*qv*T
    Cp* = Cp + (Cpv - Cp)*qv

*/

template<typename EvalT, typename Traits>
class XZHydrostatic_VirtualT_CpStar : public PHX::EvaluatorWithBaseImpl<Traits>,
                   public PHX::EvaluatorDerived<EvalT, Traits> {

public:
  typedef typename EvalT::ScalarT ScalarT;
  typedef typename EvalT::MeshScalarT MeshScalarT;

  XZHydrostatic_VirtualT_CpStar(const Teuchos::ParameterList& p,
                const Teuchos::RCP<Aeras::Layouts>& dl);

  void postRegistrationSetup(typename Traits::SetupData d,
			     PHX::FieldManager<Traits>& vm);

  void evaluateFields(typename Traits::EvalData d);

private:
  // Output:
  PHX::MDField<ScalarT,Cell,Node> temperature;
  PHX::MDField<ScalarT,Cell,Node> density;
  PHX::MDField<ScalarT,Cell,Node> qv;
  PHX::MDField<ScalarT,Cell,Node> virt_t;
  PHX::MDField<ScalarT,Cell,Node> cpstar;

  const Teuchos::ArrayRCP<std::string> tracerNames;

  const int numNodes;
  const int numLevels;
  int numTracers;
  bool vapor;

};
}

#endif
