//*****************************************************************//
//    Albany 2.0:  Copyright 2012 Sandia Corporation               //
//    This Software is released under the BSD license detailed     //
//    in the file "license.txt" in the top-level Albany directory  //
//*****************************************************************//

#include "Teuchos_TestForException.hpp"
#include "Teuchos_VerboseObject.hpp"
#include "Teuchos_RCP.hpp"
#include "Phalanx_DataLayout.hpp"
#include "Sacado_ParameterRegistration.hpp"

#include "Intrepid_FunctionSpaceTools.hpp"
#include "Aeras_Layouts.hpp"

namespace Aeras {

//**********************************************************************
template<typename EvalT, typename Traits>
XZHydrostatic_KineticEnergy<EvalT, Traits>::
XZHydrostatic_KineticEnergy(const Teuchos::ParameterList& p,
              const Teuchos::RCP<Aeras::Layouts>& dl) :
  wGradBF  (p.get<std::string> ("Weighted Gradient BF Name"),dl->node_qp_gradient),
  u  (p.get<std::string> ("Velx"), dl->node_scalar_level),
  ke (p.get<std::string> ("Kinetic Energy"), dl->node_scalar_level)
{

  this->addDependentField(u);

  this->addEvaluatedField(ke);


  this->setName("Aeras::XZHydrostatic_KineticEnergy"+PHX::TypeString<EvalT>::value);

  std::vector<PHX::DataLayout::size_type> dims;
  wGradBF.fieldTag().dataLayout().dimensions(dims);
  numNodes = dims[1];
  numQPs   = dims[2];
  numDims  = dims[3];

  u.fieldTag().dataLayout().dimensions(dims);

  numLevels =  p.get< int >("Number of Vertical Levels");
  std::cout << "Aeras::XZHydrostatic_KineticEnergy: numLevels= " << numLevels << std::endl;

  ke0 = 0.0;

}

//**********************************************************************
template<typename EvalT, typename Traits>
void XZHydrostatic_KineticEnergy<EvalT, Traits>::
postRegistrationSetup(typename Traits::SetupData d,
                      PHX::FieldManager<Traits>& fm)
{
  this->utils.setFieldData(u,fm);
  this->utils.setFieldData(ke,fm);
}

//**********************************************************************
template<typename EvalT, typename Traits>
void XZHydrostatic_KineticEnergy<EvalT, Traits>::
evaluateFields(typename Traits::EvalData workset)
{
  for (std::size_t cell=0; cell < workset.numCells; ++cell) {
    for (std::size_t node=0; node < numNodes; ++node) {

      for (std::size_t level=0; level < numLevels; ++level) {
        // Advection Term
        ke(cell,node,level) += 0.5*u(cell,node,level)*u(cell,node,level);
      }
    }
  }
}

//**********************************************************************
template<typename EvalT,typename Traits>
typename XZHydrostatic_KineticEnergy<EvalT,Traits>::ScalarT& 
XZHydrostatic_KineticEnergy<EvalT,Traits>::getValue(const std::string &n)
{
  if (n=="KineticEnergy") return ke0;
}

}
