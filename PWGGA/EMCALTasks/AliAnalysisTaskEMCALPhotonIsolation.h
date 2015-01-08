#ifndef ALIANALYSISTASKEMCALPHOTONISOLATION_H
#define ALIANALYSISTASKEMCALPHOTONISOLATION_H
/* Copyright(c) 1998-1999, ALICE Experiment at CERN, All rights reserved. *
 * See cxx source for full Copyright notice                               */

    //////////////////////////////////////////////////////////////////////////
    //                                                                      //
    //  Task for Isolated Gamma in p-p,p-Pb and eventually g-h Correlation  //
    //                                                                      //
    //  Author: Davide Francesco Lodato (Utrecht University)                //
    //          Lucile Ronflette (Subatech, Nantes)                         //
    //          Marco Marquard   (University Frankfurt am Main)             //
    //////////////////////////////////////////////////////////////////////////

    //ROOT System

class TH1;
class TH2;
class TH3;
class THnSparse;
class TList;
class TObjArray;
class AliEMCALGeometry;
class AliESDCaloCells;
class AliESDEvent;
class AliESDtrack;
class TClonesArray;
class TList;
class TString;
class AliVCluster;
class AliVParticle;
class AliESDtrackCuts;
class AliAODEvent;
class AliAODCaloCells;
class AliVCluster;
class AliMCEvent;
class AliStack;
class TParticle;
class AliClusterContainer;
class AliParticleContainer;
class AliEmcalParticle;
    //AliRoot System
class AliEMCALTrack;
    //class AliMagF;
class AliEMCALRecoUtils;
    //class AliAnalysisFilter;
class AliAODTrack;
class AliAODCaloCluster;
class AliESDCaloCluster;
class AliVCaloCells;
class AliAODMCParticle;
    //class AliEventPoolManager;

#include "AliAnalysisTaskEmcal.h"

class AliAnalysisTaskEMCALPhotonIsolation : public AliAnalysisTaskEmcal {
public:
    AliAnalysisTaskEMCALPhotonIsolation();
    AliAnalysisTaskEMCALPhotonIsolation(const char *name, Bool_t histo=kFALSE);
    virtual ~AliAnalysisTaskEMCALPhotonIsolation();

    void                     UserCreateOutputObjects();

    void                     SetIsoConeRadius(Float_t r)                                     { fIsoConeRadius = r ;}
    void                     SetEtIsoThreshold(Float_t r)                                     {fEtIsoThreshold = r ;}
    void                     SetCTMdeltaEta (Float_t r)                                      { fdetacut = r ;}
    void                     SetCTMdeltaPhi (Float_t r)                                      { fdphicut = r ;}
    void                     SetIsoMethod (Int_t r )                                         { fIsoMethod = r ;}
    void                     SetEtIsoMethod (Int_t r )                                       { fEtIsoMethod = r ;}
    void                     SetUEMethod (Int_t UE)                                          { fUEMethod = UE;}
    void                     SetOutputFormat (Int_t iOut)                                    { fWho = iOut;}
    void                     SetQA (Bool_t QA)                                               { fQA = QA;}
    void                     SetMC (Bool_t MC)                                               { fIsMC = MC;}
    void                     SetUSEofTPC (Bool_t TPC)                                        { fTPC4Iso = TPC;}
    void                     SetLCAnalysis (Bool_t LC)                                       { fisLCAnalysis = LC;}

protected:

    void                     FillQAHistograms(AliVCluster *coi, TLorentzVector vecCOI); // Fill some QA histograms
    void                     EtIsoCellPhiBand(TLorentzVector c, Float_t &etIso, Float_t &phiBand);    //EIsoCone via Cells UE via PhiBand EMCAL
    void                     EtIsoCellEtaBand(TLorentzVector c, Float_t &etIso, Float_t &etaBand);    //EIsoCone via Cells UE via EtaBand EMCAL
    void                     EtIsoClusPhiBand(TLorentzVector c, Float_t &etIso, Float_t &etaBand, Int_t index);    //EIsoCone via Clusters UE via EtaBand EMCAL
    void                     EtIsoClusEtaBand(TLorentzVector c, Float_t &etIso, Float_t &etaBand, Int_t index);    //EIsoCone via Clusters UE via EtaBand EMCAL
    void                     PtIsoTrackPhiBand(TLorentzVector c, Float_t &ptIso, Float_t &phiBand);   //PIsoCone via Track UE via PhiBand TPC
    void                     PtIsoTrackEtaBand(TLorentzVector c, Float_t &ptIso, Float_t &etaBand);   //PIsoCone via Track UE via EtaBand TPC
  //  void                     PtIsoTraClusPhiBand(TLorentzVector c, Float_t &ptIso, Float_t &phiBand); //(P+E)IsoCone via Track/Clus UE via PhiBand TPC+EMCAL
  //  void                     PtIsoTraClusEtaBand(TLorentzVector c, Float_t &ptIso, Float_t &etaBand); //(P+E)IsoCone via Track/Clus UE via EtaBand TPC+EMCAL
    void                     PtIsoTrackOrthCones(TLorentzVector c, Float_t &ptIso, Float_t &cones);   //PIsoCone via Tracks UE via Orthogonal Cones in Phi
    void                     PtIsoTrackFullTPC(TLorentzVector c, Float_t &ptIso, Float_t &full);      //PIsoCone via Tracks UE via FullTPC - IsoCone - B2BEtaBand
//    Bool_t                   ClustTrackMatching(AliVCluster *cluster);
    Bool_t                   ClustTrackMatching(AliEmcalParticle *emccluster);
    Bool_t                   CheckBoundaries(TLorentzVector vecCOI);
   // void                     FillNCOutput(AliVCluster *COI, TLorentzVector vecCOI, Int_t index);

    Float_t*                 GenerateFixedBinArray(Int_t n, Float_t min, Float_t max) const;
    void                     ExecOnce();
    Bool_t                   Run();
    void                     AnalyzeMC();
    void                     LookforParticle(Int_t, Double_t, Double_t, Double_t,Double_t,Double_t, Int_t);


    using AliAnalysisTaskEmcal::FillGeneralHistograms;
    Bool_t FillGeneralHistograms(AliVCluster *COI, TLorentzVector VecCOI, Int_t index);
    //Bool_t                   FillGeneralHistograms(AliVCluster *COI, TLorentzVector VecCOI, Int_t index);

  AliAODEvent *fAOD;       //!
  AliVEvent *fVevent;      //! AliVEvent
  //    TObjArray                   fParticleCollArray;              // Neutral Clusters collection array
  TClonesArray               *fNCluster;                       // Neutral clusters
  TClonesArray               *fAODMCParticles; //!
  TClonesArray               *fTracksAna;             //! hybrid track array in
  AliStack                   *fStack;//!

    Int_t       fWho;           // MODE for the Output Object (TTree or THnSparse)


		//IMPLEMENT ALL THE HISTOGRAMS AND ALL THE OUTPUT OBJECTS WE WANT!!!
   //    TList       *fOutputList; //! Output list
//    TGeoHMatrix *fGeomMatrix[12];//! Geometry misalignment matrices for EMCal


    TH1        *fTrackMult;                      //!Track Multiplicity ---QA
    TH1        *fTrackMultEMCAL;                 //!Track Multiplicity EMCAL ---QA
    TH1        *fClustMult;                      //!Cluster Multiplicity EMCAL ---QA
    TH1        *fPVZBefore;                      //!Z Vertex distribution before cuts. ---QA
    TH2        *fEtaPhiCell;                     //!EMCAL Active Cells Distribution EtaPhi ---QA
    TH2        *fEtaPhiClus;                     //!EMCAL Cluster Distribution EtaPhi ---QA
    TH2        *fClusEvsClusT;                   //!Cluster Energy vs Cluster Time ---QA
    TH1        *fVz;                             //! Veretex Z distribution
    TH1        *fEvents;                         //! Number of Events
    TH1        *fPT;                             //!Pt distribution
    TH1        *fE;                              //!E distribution
    TH1        *fPtaftTime;                       //!E distribution for clusters after cluster time cut
    TH1        *fPtaftTM;                         //!E distribution for neutral clusters
    TH1        *fPtaftFC;                         //!E distribution for clusters after fiducial cut
    TH1        *fPtaftM02C;                       //!E distribution for clusters after shower shape cut
    TH1        *fClusTime;                       //!Time distribution for clusters
    TH2        *fM02;                            //!Squared_Lambda0 distribution
    TH1        *fNLM;                            //!NLM distribution
    TH1        *fDeltaETAClusTrack;              //!dEta Cluster-Track!
    TH1        *fDeltaPHIClusTrack;              //!dPhi Cluster-Track!
    TH1        *fDeltaETAClusTrackMatch;              //!dEta Cluster-Track matched!
    TH1        *fDeltaPHIClusTrackMatch;              //!dPhi Cluster-Track matched!
    TH2        *fDeltaETAClusTrackVSpT;          //!dEta Cluster-Track VS pT!
    TH2        *fDeltaPHIClusTrackVSpT;          //!dPhi Cluster-Track VS pT!
    TH1        *fEtIsoCells;                     //!Isolation Energy with EMCAL Cells
    TH2        *fEtIsoClust;                     //!Isolation Energy with EMCAL Clusters
    TH2        *fPtIsoTrack;                     //!Isolation Pt with Tracks
    TH1        *fPtEtIsoTC;                      //!Isolation with Pt from Tracks and Et from NON-Matched Clusters
    TH2        *fPhiBandUEClust;                 //!UE with Phi Band (Clusters)
    TH2        *fEtaBandUEClust;                 //!UE with Eta Band (Clusters)
    TH2        *fPhiBandUECells;                 //!UE with Phi Band (Cells)
    TH2        *fEtaBandUECells;                 //!UE with Eta Band (Cells)
    TH2        *fPhiBandUETracks;                //!UE with Phi Band (Tracks)
    TH2        *fEtaBandUETracks;                //!UE with Eta Band (Tracks)
    TH2        *fPerpConesUETracks;              //!UE with Cones (Tracks ONLY)
    TH2        *fTPCWithoutIsoConeB2BbandUE;     //!UE with Full TPC except IsoCone and EtaBand in Back2Back
    TH1        *fNTotClus10GeV;                  //!number of TOTAL clusters with Energy bigger than 10 GeV
    TH1        *fRecoPV;                         //! primary vertex reconstruction
    TH1        *fEtIsolatedCells;                //! Isolated photons, isolation with cells
    TH1        *fEtIsolatedClust;                //! Isolated photons, isolation with clusters
    TH1        *fPtIsolatedNClust;               //! Isolated neutral clusters
    TH1        *fPtIsolatedNTracks;               //! Isolated neutral clusters with tracks
    TH1        *fEtIsolatedTracks;               //! Isolated photons, isolation with tracks
    TH2        *fPtvsM02iso;                     //! Isolated clusters, pt distribution vs M02
    TH2        *fPtvsM02noiso;                   //! Non isolated clusters, pt distribution vs M02
    TH2        *fTestIndex;                      //! Index and local index test
    TH2        *fTestIndexE;
    TH2        *fTestLocalIndexE;
    TH2        *fTestEnergyCone;                 //! ernergy cone clusters vs tracks
    TH2        *fTestEtaPhiCone;

    THnSparse   *fOutputTHnS;                    //! 1st Method 4 Output
    THnSparse   *fOutMCTruth;                    //! 1st Method 4 MC truth Output //Isolation on pTMax
    THnSparse   *fOutClustMC;                    //! 1st Method 4 MC+Truth Output via Clusterlabel

    TTree       *fOutputQATree;                  //! 2nd method 4 QA Output
    TTree       *fOutputTree;                    //! 2nd Method 4 Output

    TH3        *fphietaPhotons; //!
    TH3        *fphietaOthers; //!
    TH3        *fphietaOthersBis;//!

    Float_t     fIsoConeRadius;                  // Radius for the Isolation Cont
    Int_t       fEtIsoMethod;                    // Isolation definition 0=SumEt<EtThr, 1=SumEt<%Ephoton, 2=Etmax<EtThr
    Double_t    fEtIsoThreshold;                 // Et isolation threshold, supposed to be % if method one is choosed
    Double_t    fdetacut;                        // cut on deta between track and cluster
    Double_t    fdphicut;                        // cut on dphi between track and cluster
    Double_t    fM02mincut;                      // lambda0^2 minimum cut
    Double_t    fM02maxcut;                      // lambda0^2 maximum cut
    Bool_t      fQA;                             // Flag for few further QA plots wrt the ones already done in the EMCALTask
    Bool_t      fIsMC;                           // Flag for MC Truth Analysis
    Bool_t      fTPC4Iso;                        //0=EMCAL_ONLY; 1=EMCAL+TPC
    Int_t       fIsoMethod;                      //0=Cells, 1=Clusters (EMCAL_ONLY),  2=Tracks (EMCAL w/o TPC)
    Int_t       fUEMethod;                       //0=PhiBand, 1=EtaBand, (EMCAL or TPC) 2= Ort Cones, 3=FullTPC (only with TPC)
    Int_t       fNDimensions;                    //!number of Dimensions for the THnSPARSE
    Int_t       fMCDimensions;
    Int_t       fMCQAdim;                        //!
    Bool_t      fisLCAnalysis;                   // Flag to pass from Leading Clusters Analysis to a NC One
    Int_t       fTest1;
    Int_t       fTest2;

// Initialization for TTree variables
    Double_t    fEClustersT;                     // E for all clusters
    Double_t    fPtClustersT;                    // Pt for all clusters
    Double_t    fEtClustersT;                    // Et for all clusters
    Double_t    fEtaClustersT;                   // Eta for all clusters
    Double_t    fPhiClustersT;                   // Phi for all clusters
    Double_t    fM02ClustersT;                   // lamnda0^2 for all clusters

    Int_t       fevents;                         // N events
    Int_t       fNClustersT;                     // Clusters multiplicity
    Double_t    flambda0T;                       // M02 for considered clusters (leading one or all depending on flag)
    Double_t    fM02isoT;                        // M02 for isolated clusters
    Double_t    fM02noisoT;                      // M02 for non isolated clusters
    Double_t    fPtnoisoT;                       // Pt for non isolated clusters
    Double_t    fEtT;                            // Et for considered clusters (leading one or all depending on flag)
    Double_t    fPtT;                            // Pt for considered clusters (leading one or all depending on flag)
    Double_t    fPtisoT;                         // Pt for all isolated neutral clusters
    Double_t    fEtisolatedT;                         // Et for isolated clusters
    Double_t    fPtisolatedT;                         // Pt for isolated clusters
    Double_t    fetaT;                           // Eta for considered clusters
    Double_t    fphiT;                           // Phi for considered clusters
    Double_t    fsumEtisoconeT;                  // sum Et  in cone
    Double_t    fsumEtUE;                        // sum UE


    //  AliParticleContainer       *fTracksCont;     //!Tracks
    //  AliParticleContainer       *fclusters;                       //!Container for Particle container 4 clusters

private:
   AliAnalysisTaskEMCALPhotonIsolation(const AliAnalysisTaskEMCALPhotonIsolation&);            // not implemented
   AliAnalysisTaskEMCALPhotonIsolation &operator=(const AliAnalysisTaskEMCALPhotonIsolation&); // not implemented


    ClassDef(AliAnalysisTaskEMCALPhotonIsolation, 1)    //EMCAL Neutrals base analysis task
};
#endif

