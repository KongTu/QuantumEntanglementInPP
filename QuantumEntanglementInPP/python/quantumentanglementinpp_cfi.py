import FWCore.ParameterSet.Config as cms
				
ana = cms.EDAnalyzer('QuantumEntanglementInPP',
                                                  vertexName = cms.InputTag('offlinePrimaryVertices'),
                		 		  trackName = cms.InputTag('generalTracks'),
                                                  towerName = cms.InputTag("towerMaker"),
                                                  offlineDCA = cms.untracked.double(3.0),
                                                  offlineptErr = cms.untracked.double(0.1),
			  		  	  offlinenhits = cms.untracked.double(0),
						  offlineChi2 = cms.untracked.double(999.9),
              					  useEtaGap = cms.untracked.bool(False),
						  doEffCorrection = cms.untracked.bool(False),
              doGenParticle = cms.untracked.bool(True),
						  Nmin = cms.untracked.int32(1),
                                                  Nmax = cms.untracked.int32(10000),
                                                  eff = cms.untracked.int32(1),
                                                  vzLow = cms.untracked.double(0.0),
                                                  vzHigh = cms.untracked.double(15.0),
                                                  ptLow = cms.untracked.double(0.3),
						  ptHigh = cms.untracked.double(3.0),
      
                                                  etaBins = cms.untracked.vdouble(-2.4,-1.4,-0.7,0.0,0.7,1.4,2.4),
                                                
						  ptBins = cms.untracked.vdouble(0.3,0.4,0.5,0.6,0.7,0.8,0.9,1.0,1.1,1.2,1.3,1.4,1.5,
                                                                                 1.6,1.7,1.8,1.9,2.0,2.1,2.2,2.3,2.4,2.5,2.6,2.7,2.8,2.9,3.0),

                                              

)

