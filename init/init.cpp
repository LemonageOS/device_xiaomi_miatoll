/*
 * Copyright (C) 2020 The LineageOS Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <cstdlib>
#include <cstring>
#include <sys/sysinfo.h>
#include <vector>

#include <android-base/properties.h>
#define _REALLY_INCLUDE_SYS__SYSTEM_PROPERTIES_H_
#include <sys/_system_properties.h>

#include "init_common.h"
#include "vendor_init.h"

using android::base::GetProperty;

std::vector<std::string> ro_props_default_source_order = {
    "",
    "odm.",
    "product.",
    "system.",
    "vendor.",
    "system_ext.",
};

void set_ro_build_prop(const std::string &source, const std::string &prop,
        const std::string &value, bool product = false) {
    std::string prop_name;

    if (product) {
        prop_name = "ro.product." + source + prop;
    } else {
        prop_name = "ro." + source + "build." + prop;
    }

    property_override(prop_name.c_str(), value.c_str(), false);
}

void set_device_props(const std::string brand, const std::string device, const std::string model) {
    for (const auto &source : ro_props_default_source_order) {
        set_ro_build_prop(source, "brand", brand, true);
        set_ro_build_prop(source, "device", device, true);
        set_ro_build_prop(source, "model", model, true);
    }

}

void load_device_properties() {
    std::string hwname = GetProperty("ro.boot.hwname", "");
    std::string region = GetProperty("ro.boot.hwc", "");

    if (hwname == "curtana") {
        if (region == "India") {
            set_device_props("Redmi", "curtana", "Redmi Note 10 Lite");
            property_override("ro.build.fingerprint", "Redmi/curtana_in1/curtana:12/RKQ1.211019.001/V14.0.5.0.SJWINRF:user/release-keys");
            property_override("ro.build.description", "curtana_in1-user 12 RKQ1.211019.001 V14.0.5.0.SJWINRF release-keys");
        } else {
            set_device_props("Redmi", "curtana", "Redmi Note 9S");
            property_override("ro.build.fingerprint", "Redmi/curtana_global/curtana:12/RKQ1.211019.001/V14.0.4.0.SJWMIXM:user/release-keys");
            property_override("ro.build.description", "curtana_global-user 12 RKQ1.211019.001 V14.0.4.0.SJWMIXM release-keys");
        }
    } else if (hwname == "excalibur") {
        set_device_props("Redmi", "excalibur", "Redmi Note 9 Pro Max");
        property_override("ro.build.fingerprint", "Redmi/excalibur_in/excalibur:12/RKQ1.211019.001/V14.0.2.0.SJXINXM:user/release-keys");
        property_override("ro.build.description", "excalibur_in-user 12 RKQ1.211019.001 V14.0.2.0.SJXINXM release-keys");
    } else if (hwname == "gram") {
        set_device_props("POCO", "gram", "POCO M2 Pro");
        property_override("ro.build.fingerprint", "POCO/gram_in/gram:12/RKQ1.211019.001/V14.0.5.0.SJPINXM:user/release-keys");
        property_override("ro.build.description", "gram_in-user 12 RKQ1.211019.001 V14.0.5.0.SJPINXM release-keys");
    } else if (hwname == "joyeuse") {
        set_device_props("Redmi", "joyeuse", "Redmi Note 9 Pro");
        property_override("ro.build.fingerprint", "Redmi/joyeuse_global/joyeuse:12/RKQ1.211019.001/V14.0.3.0.SJZMIXM:user/release-keys");
        property_override("ro.build.description", "joyeuse_global-user 12 RKQ1.211019.001 V14.0.3.0.SJZMIXM release-keys");
    }
}

void vendor_load_properties() {
    load_common_properties();
    load_device_properties();
}
