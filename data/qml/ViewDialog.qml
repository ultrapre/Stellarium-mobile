//silas

import QtQuick 2.2
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.12
import QtQuick.Controls.Styles 1.4
import Stellarium 1.0

StelDialog {
    id: root
    title: qsTr("View")
    width: rootStyle.niceMenuWidth


//	property string current: stellarium.currentSkyCultureI18
    ListView {
        id: list
        width: 140*rootStyle.scale
        height: 400*rootStyle.scale
        StelListItem {
            id: list_dso
            text: qsTr("DSO")
        }
        StelListItem {
            y:list_dso.height*1
            id: list_ss
            text: qsTr("Solar")
        }
    }

    Flickable {
//        left: list.right
//        right: parent.right
        anchors {
            left: list.right
            top: parent.top
            right: parent.right
            bottom: parent.bottom
            margins: rootStyle.margin

        }
        clip: true
        contentWidth: width
        contentHeight: dsoAmountview.height+dsoLimitview.height+dsolistview.height+dsotypeview.height+dsoAdvView.height
        flickableDirection: Flickable.VerticalFlick


        GridLayout{
            id:dsoAmountview;
            columns: 2
            y:0
            Text{
                color: "white"
                text: "hints"
            }

            Slider{
                id: hintsAmount
                from: 0
                value: stellarium.getDoubleSetting("astro/nebula_hints_amount")
                to: 10
                live: false
                onValueChanged: {
                    stellarium.writeDoubleSetting("astro/nebula_hints_amount", value)
                    stellarium.updateSkyView()
                }
            }
            Text{
                color: "white"
                text: "labels"
            }
            Slider{
                id: labelsAmount
                from: 0
                value: stellarium.getDoubleSetting("astro/nebula_labels_amount")
                to: 10
                live: false
                onValueChanged: {
                    stellarium.writeDoubleSetting("astro/nebula_labels_amount", value)
                    stellarium.updateSkyView()
                }
            }
        }

        GridLayout{
            id:dsoLimitview;
            columns: 1
            y:dsoAmountview.height+dsoAmountview.y
            CheckBox{
                id:chMagLimit
                checked: stellarium.getboolSetting("astro/flag_nebula_magnitude_limit")
                onCheckedChanged: {
                stellarium.writeSetting("astro/flag_nebula_magnitude_limit", checked)
//                stellarium.setFlagNebulaMagnitudeLimit(checked)
                stellarium.flagNebulaMagnitudeLimit = checked
//                stellarium.updateSkyView()
                }
                text: qsTr("VMag Limit")
            }
            Slider{
//                width: dsoLimitview.width - chMagLimit.width
                from: 3
                to: 21
                value: 21
                live: false
                onValueChanged: {
                    stellarium.writeDoubleSetting("astro/nebula_magnitude_limit", value) //*(21-3)/5
                    stellarium.setCustomNebulaMagnitudeLimit(value)
//                    stellarium.update()
                }
            }
            CheckBox{
//                width: dsoLimitview.width - chMagLimit.width
                id:chSizeLimits
                checked: stellarium.getboolSetting("astro/flag_size_limits_usage")
                onCheckedChanged: {
                stellarium.writeSetting("astro/flag_size_limits_usage", checked)
                stellarium.updateSkyView()}
                text: qsTr("Size Limit")
            }
            RangeSlider{
                from: 0
                to: 10
                first.value: Math.log(stellarium.getDoubleSetting("astro/size_limit_min"))/Math.log(Math.E)/0.7
                second.value: Math.log(stellarium.getDoubleSetting("astro/size_limit_max"))/Math.log(Math.E)/0.7
                live: false
                first.onValueChanged: {
                    stellarium.writeDoubleSetting("astro/size_limit_min", Math.exp(0.7*first.value))//first.value*first.value/1200
                    stellarium.updateSkyView()
                }
                second.onValueChanged: {
                    stellarium.writeDoubleSetting("astro/size_limit_max", Math.exp(0.7*second.value))
                    stellarium.updateSkyView()
                }
            }
        }



        GridLayout {
                  id:dsolistview;
                  columns: 3
                  y:dsoLimitview.height+dsoLimitview.y
                  CheckBox {id:chM
                  checked: stellarium.getboolSetting("dso_catalog_filters/flag_show_m")
                  onCheckedChanged: {
                  stellarium.writeSetting("dso_catalog_filters/flag_show_m", chM.checked)
                  stellarium.updateSkyView()}
                  text: qsTr("M")}
                  CheckBox {id:chC
                  checked: stellarium.getboolSetting("dso_catalog_filters/flag_show_c")
                  onCheckedChanged: {
                  stellarium.writeSetting("dso_catalog_filters/flag_show_c", chC.checked)
                  stellarium.updateSkyView()}
                  text: qsTr("C")}
                  CheckBox {id:chNGC
                  checked: stellarium.getboolSetting("dso_catalog_filters/flag_show_ngc")
                  onCheckedChanged: {
                  stellarium.writeSetting("dso_catalog_filters/flag_show_ngc", chNGC.checked)
                  stellarium.updateSkyView()}
                  text: qsTr("NGC")}
                  CheckBox {id:chIC
                  checked: stellarium.getboolSetting("dso_catalog_filters/flag_show_ic")
                  onCheckedChanged: {
                  stellarium.writeSetting("dso_catalog_filters/flag_show_ic", chIC.checked)
                  stellarium.updateSkyView()}
                  text: qsTr("IC")}
                  CheckBox {id:chB
                  checked: stellarium.getboolSetting("dso_catalog_filters/flag_show_b")
                  onCheckedChanged: {
                  stellarium.writeSetting("dso_catalog_filters/flag_show_b", chB.checked)
                  stellarium.updateSkyView()}
                  text: qsTr("B")}
                  CheckBox {id:chSh2
                  checked: stellarium.getboolSetting("dso_catalog_filters/flag_show_sh2")
                  onCheckedChanged: {
                  stellarium.writeSetting("dso_catalog_filters/flag_show_sh2", chSh2.checked)
                  stellarium.updateSkyView()}
                  text: qsTr("Sh2")}
                  CheckBox {id:chvdB
                  checked: stellarium.getboolSetting("dso_catalog_filters/flag_show_vdb")
                  onCheckedChanged: {
                  stellarium.writeSetting("dso_catalog_filters/flag_show_vdb", chvdB.checked)
                  stellarium.updateSkyView()}
                  text: qsTr("vdB")}
                  CheckBox {id:chRCW
                  checked: stellarium.getboolSetting("dso_catalog_filters/flag_show_rcw")
                  onCheckedChanged: {
                  stellarium.writeSetting("dso_catalog_filters/flag_show_rcw", chRCW.checked)
                  stellarium.updateSkyView()}
                  text: qsTr("RCW")}
                  CheckBox {id:chLDN
                  checked: stellarium.getboolSetting("dso_catalog_filters/flag_show_ldn")
                  onCheckedChanged: {
                  stellarium.writeSetting("dso_catalog_filters/flag_show_ldn", chLDN.checked)
                  stellarium.updateSkyView()}
                  text: qsTr("LDN")}
                  CheckBox {id:chLBN
                  checked: stellarium.getboolSetting("dso_catalog_filters/flag_show_lbn")
                  onCheckedChanged: {
                  stellarium.writeSetting("dso_catalog_filters/flag_show_lbn", chLBN.checked)
                  stellarium.updateSkyView()}
                  text: qsTr("LBN")}
                  CheckBox {id:chCr
                  checked: stellarium.getboolSetting("dso_catalog_filters/flag_show_cr")
                  onCheckedChanged: {
                  stellarium.writeSetting("dso_catalog_filters/flag_show_cr", chCr.checked)
                  stellarium.updateSkyView()}
                  text: qsTr("Cr")}
                  CheckBox {id:chMel
                  checked: stellarium.getboolSetting("dso_catalog_filters/flag_show_mel")
                  onCheckedChanged: {
                  stellarium.writeSetting("dso_catalog_filters/flag_show_mel", chMel.checked)
                  stellarium.updateSkyView()}
                  text: qsTr("Mel")}
                  CheckBox {id:chPGC
                  checked: stellarium.getboolSetting("dso_catalog_filters/flag_show_pgc")
                  onCheckedChanged: {
                  stellarium.writeSetting("dso_catalog_filters/flag_show_pgc", chPGC.checked)
                  stellarium.updateSkyView()}
                  text: qsTr("PGC")}
                  CheckBox {id:chUGC
                  checked: stellarium.getboolSetting("dso_catalog_filters/flag_show_ugc")
                  onCheckedChanged: {
                  stellarium.writeSetting("dso_catalog_filters/flag_show_ugc", chUGC.checked)
                  stellarium.updateSkyView()}
                  text: qsTr("UGC")}
                  CheckBox {id:chCed
                  checked: stellarium.getboolSetting("dso_catalog_filters/flag_show_ced")
                  onCheckedChanged: {
                  stellarium.writeSetting("dso_catalog_filters/flag_show_ced", chCed.checked)
                  stellarium.updateSkyView()}
                  text: qsTr("Ced")}
                  CheckBox {id:chArp
                  checked: stellarium.getboolSetting("dso_catalog_filters/flag_show_arp")
                  onCheckedChanged: {
                  stellarium.writeSetting("dso_catalog_filters/flag_show_arp", chArp.checked)
                  stellarium.updateSkyView()}
                  text: qsTr("Arp")}
                  CheckBox {id:chVV
                  checked: stellarium.getboolSetting("dso_catalog_filters/flag_show_vv")
                  onCheckedChanged: {
                  stellarium.writeSetting("dso_catalog_filters/flag_show_vv", chVV.checked)
                  stellarium.updateSkyView()}
                  text: qsTr("VV")}
                  CheckBox {id:chPK
                  checked: stellarium.getboolSetting("dso_catalog_filters/flag_show_pk")
                  onCheckedChanged: {
                  stellarium.writeSetting("dso_catalog_filters/flag_show_pk", chPK.checked)
                  stellarium.updateSkyView()}
                  text: qsTr("PK")}
                  CheckBox {id:chPNG
                  checked: stellarium.getboolSetting("dso_catalog_filters/flag_show_png")
                  onCheckedChanged: {
                  stellarium.writeSetting("dso_catalog_filters/flag_show_png", chPNG.checked)
                  stellarium.updateSkyView()}
                  text: qsTr("PN G")}
                  CheckBox {id:chSNRG
                  checked: stellarium.getboolSetting("dso_catalog_filters/flag_show_snrg")
                  onCheckedChanged: {
                  stellarium.writeSetting("dso_catalog_filters/flag_show_snrg", chSNRG.checked)
                  stellarium.updateSkyView()}
                  text: qsTr("SNR G")}
                  CheckBox {id:chACO
                  checked: stellarium.getboolSetting("dso_catalog_filters/flag_show_aco")
                  onCheckedChanged: {
                  stellarium.writeSetting("dso_catalog_filters/flag_show_aco", chACO.checked)
                  stellarium.updateSkyView()}
                  text: qsTr("ACO")}
                  CheckBox {id:chHCG
                  checked: stellarium.getboolSetting("dso_catalog_filters/flag_show_hcg")
                  onCheckedChanged: {
                  stellarium.writeSetting("dso_catalog_filters/flag_show_hcg", chHCG.checked)
                  stellarium.updateSkyView()}
                  text: qsTr("HCG")}
                  CheckBox {id:chESO
                  checked: stellarium.getboolSetting("dso_catalog_filters/flag_show_eso")
                  onCheckedChanged: {
                  stellarium.writeSetting("dso_catalog_filters/flag_show_eso", chESO.checked)
                  stellarium.updateSkyView()}
                  text: qsTr("ESO")}
                  CheckBox {id:chvdBH
                  checked: stellarium.getboolSetting("dso_catalog_filters/flag_show_vdbh")
                  onCheckedChanged: {
                  stellarium.writeSetting("dso_catalog_filters/flag_show_vdbh", chvdBH.checked)
                  stellarium.updateSkyView()}
                  text: qsTr("vdBH")}
                  CheckBox {id:chDWB
                  checked: stellarium.getboolSetting("dso_catalog_filters/flag_show_dwb")
                  onCheckedChanged: {
                  stellarium.writeSetting("dso_catalog_filters/flag_show_dwb", chDWB.checked)
                  stellarium.updateSkyView()}
                  text: qsTr("DWB")}
                  CheckBox {id:chTr
                  checked: stellarium.getboolSetting("dso_catalog_filters/flag_show_tr")
                  onCheckedChanged: {
                  stellarium.writeSetting("dso_catalog_filters/flag_show_tr", chTr.checked)
                  stellarium.updateSkyView()}
                  text: qsTr("Tr")}
                  CheckBox {id:chSt
                  checked: stellarium.getboolSetting("dso_catalog_filters/flag_show_st")
                  onCheckedChanged: {
                  stellarium.writeSetting("dso_catalog_filters/flag_show_st", chSt.checked)
                  stellarium.updateSkyView()}
                  text: qsTr("St")}
                  CheckBox {id:chRu
                  checked: stellarium.getboolSetting("dso_catalog_filters/flag_show_ru")
                  onCheckedChanged: {
                  stellarium.writeSetting("dso_catalog_filters/flag_show_ru", chRu.checked)
                  stellarium.updateSkyView()}
                  text: qsTr("Ru")}
                  CheckBox {id:chvdBHa
                  checked: stellarium.getboolSetting("dso_catalog_filters/flag_show_vdbha")
                  onCheckedChanged: {
                  stellarium.writeSetting("dso_catalog_filters/flag_show_vdbha", chvdBHa.checked)
                  stellarium.updateSkyView()}
                  text: qsTr("vdB-Ha")}
                  CheckBox {id:chOther
                  checked: stellarium.getboolSetting("dso_catalog_filters/flag_show_other")
                  onCheckedChanged: {
                  stellarium.writeSetting("dso_catalog_filters/flag_show_other", chvdBHa.checked)
                  stellarium.updateSkyView()}
                  text: qsTr("Other")}
              }


        GridLayout {
                  id:dsotypeview;
                  columns: 1
                  y:dsolistview.height+dsolistview.y
                  CheckBox {id:chDSOTypeFilter
                  checked: stellarium.getboolSetting("astro/flag_use_type_filter")
                  onCheckedChanged: {
                  stellarium.writeSetting("astro/flag_use_type_filter", chDSOTypeFilter.checked)
                  stellarium.updateSkyView()}
                  text: qsTr("Type Filter")}

                  CheckBox {id:ch_galaxies
                  checked: stellarium.getboolSetting("dso_type_filters/flag_show_galaxies")
                  onCheckedChanged: {
                  stellarium.writeSetting("dso_type_filters/flag_show_galaxies", ch_galaxies.checked)
                  stellarium.updateSkyView()}
                  text: qsTr("galaxies")}
                  CheckBox {id:ch_active_galaxies
                  checked: stellarium.getboolSetting("dso_type_filters/flag_show_active_galaxies")
                  onCheckedChanged: {
                  stellarium.writeSetting("dso_type_filters/flag_show_active_galaxies", ch_active_galaxies.checked)
                  stellarium.updateSkyView()}
                  text: qsTr("active_galaxies")}
                  CheckBox {id:ch_interacting_galaxies
                  checked: stellarium.getboolSetting("dso_type_filters/flag_show_interacting_galaxies")
                  onCheckedChanged: {
                  stellarium.writeSetting("dso_type_filters/flag_show_interacting_galaxies", ch_interacting_galaxies.checked)
                  stellarium.updateSkyView()}
                  text: qsTr("interacting_galaxies")}
                  CheckBox {id:ch_open_clusters
                  checked: stellarium.getboolSetting("dso_type_filters/flag_show_open_clusters")
                  onCheckedChanged: {
                  stellarium.writeSetting("dso_type_filters/flag_show_open_clusters", ch_open_clusters.checked)
                  stellarium.updateSkyView()}
                  text: qsTr("open_clusters")}
                  CheckBox {id:ch_globular_clusters
                  checked: stellarium.getboolSetting("dso_type_filters/flag_show_globular_clusters")
                  onCheckedChanged: {
                  stellarium.writeSetting("dso_type_filters/flag_show_globular_clusters", ch_globular_clusters.checked)
                  stellarium.updateSkyView()}
                  text: qsTr("globular_clusters")}
                  CheckBox {id:ch_bright_nebulae
                  checked: stellarium.getboolSetting("dso_type_filters/flag_show_bright_nebulae")
                  onCheckedChanged: {
                  stellarium.writeSetting("dso_type_filters/flag_show_bright_nebulae", ch_bright_nebulae.checked)
                  stellarium.updateSkyView()}
                  text: qsTr("bright_nebulae")}
                  CheckBox {id:ch_dark_nebulae
                  checked: stellarium.getboolSetting("dso_type_filters/flag_show_dark_nebulae")
                  onCheckedChanged: {
                  stellarium.writeSetting("dso_type_filters/flag_show_dark_nebulae", ch_dark_nebulae.checked)
                  stellarium.updateSkyView()}
                  text: qsTr("dark_nebulae")}
                  CheckBox {id:ch_planetary_nebulae
                  checked: stellarium.getboolSetting("dso_type_filters/flag_show_planetary_nebulae")
                  onCheckedChanged: {
                  stellarium.writeSetting("dso_type_filters/flag_show_planetary_nebulae", ch_planetary_nebulae.checked)
                  stellarium.updateSkyView()}
                  text: qsTr("planetary_nebulae")}
                  CheckBox {id:ch_hydrogen_regions
                  checked: stellarium.getboolSetting("dso_type_filters/flag_show_hydrogen_regions")
                  onCheckedChanged: {
                  stellarium.writeSetting("dso_type_filters/flag_show_hydrogen_regions", ch_hydrogen_regions.checked)
                  stellarium.updateSkyView()}
                  text: qsTr("hydrogen_regions")}
                  CheckBox {id:ch_supernova_remnants
                  checked: stellarium.getboolSetting("dso_type_filters/flag_show_supernova_remnants")
                  onCheckedChanged: {
                  stellarium.writeSetting("dso_type_filters/flag_show_supernova_remnants", ch_supernova_remnants.checked)
                  stellarium.updateSkyView()}
                  text: qsTr("supernova_remnants")}
                  CheckBox {id:ch_galaxy_clusters
                  checked: stellarium.getboolSetting("dso_type_filters/flag_show_galaxy_clusters")
                  onCheckedChanged: {
                  stellarium.writeSetting("dso_type_filters/flag_show_galaxy_clusters", ch_galaxy_clusters.checked)
                  stellarium.updateSkyView()}
                  text: qsTr("galaxy_clusters")}
                  CheckBox {id:ch_other
                  checked: stellarium.getboolSetting("dso_type_filters/flag_show_other")
                  onCheckedChanged: {
                  stellarium.writeSetting("dso_type_filters/flag_show_other", ch_other.checked)
                  stellarium.updateSkyView()}
                  text: qsTr("other")}
        }



        GridLayout {
                  id:dsoAdvView;
                  columns: 1
                  y:dsotypeview.height+dsotypeview.y

                  CheckBox{
                      id:chHintsProportional
                      checked: stellarium.getboolSetting("astro/flag_nebula_hints_proportional")
                      onCheckedChanged: {
                      stellarium.writeSetting("astro/flag_nebula_hints_proportional", checked)
                      stellarium.updateSkyView()}
                      text: qsTr("Use proportional hints")
                  }
                  CheckBox{
                      id:chFlagOutlines
                      checked: stellarium.getboolSetting("astro/flag_dso_outlines_usage")
                      onCheckedChanged: {
                      stellarium.writeSetting("astro/flag_dso_outlines_usage", checked)
                      stellarium.updateSkyView()}
                      text: qsTr("outlines for dso")
                  }
                  CheckBox{
                      id:chFlagAdditionalNames
                      checked: stellarium.getboolSetting("astro/flag_dso_additional_names")
                      onCheckedChanged: {
                      stellarium.writeSetting("astro/flag_dso_additional_names", checked)
                      stellarium.updateSkyView()}
                      text: qsTr("Use additional names of DSO")
                  }
                  CheckBox{
                      id:chDesignationUsage
                      checked: stellarium.getboolSetting("astro/flag_dso_designation_usage")
                      onCheckedChanged: {
                      stellarium.writeSetting("astro/flag_dso_designation_usage", checked)
                      stellarium.updateSkyView()}
                      text: qsTr("Use designations for screen labels")
                  }
                  CheckBox{
                      id:chFlagSurfaceBrightnessUsage
                      checked: stellarium.getboolSetting("astro/flag_surface_brightness_usage")
                      onCheckedChanged: {
                      stellarium.writeSetting("astro/flag_surface_brightness_usage", checked)
                      stellarium.updateSkyView()}
                      text: qsTr("Use surface brightness")
                  }
        }
//              Button{
//                  text: "获取CheckBox状态"
//                  onClicked: {
//                      console.log(chM.checked)
//                      console.log(chNGC.checked)
//                      console.log(chPGC.checked)
//                  }
//              }
    }
}
