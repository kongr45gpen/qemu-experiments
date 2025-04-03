#include "InternalFlash.hpp"

static constexpr uint8_t PagesPerSector = 64; // Unsure

FlashDriver::FlashDriver() {
    fptr = fopen("MCU_FLASH", "wb+");
    if (fptr == nullptr) {
        LOG_ERROR << "  [QEMU] Failed to open MCU_FLASH";
    } else {
        LOG_INFO << "   [QEMU] MCU_FLASH opened successfully";
    }

    // Fill the file with ones
    uint8_t fill = 0xFF;
    for (size_t i = 0; i < (EndAddress - StartAddress); ++i) {
        fwrite(&fill, 1, 1, fptr);
    }
}

[[nodiscard]] FlashDriver::EFCError FlashDriver::getEFCError() {
    return EFCError::NONE;
}

[[nodiscard]] FlashDriver::EFCError
FlashDriver::eraseSector(FlashAddress_t address) {
    FlashAddress_t endAddress = address + (PagesPerSector * WordsPerPage * 4);

    if (endAddress > EndAddress) {
        endAddress = EndAddress;
    }

    if (not isAddressSafe(address)) {
        return EFCError::ADDRESS_UNSAFE;
    }

    fseek(fptr, 0, SEEK_SET);
    uint8_t fill = 0xFF;
    for (FlashAddress_t addr = address; addr < endAddress; addr++) {
        size_t bytes = fwrite(&fill, 1, 1, fptr);
        if (bytes != 1) {
            LOG_ERROR << "  [QEMU] Failed to write to MCU_FLASH. Wrote " << bytes
                      << " bytes instead of " << 1;
            return EFCError::FLASH_ERROR;
        }
    }

    return EFCError::NONE;
}

[[nodiscard]] FlashDriver::EFCError FlashDriver::waitForResponse() {
    return EFCError::NONE;
}

[[nodiscard]] FlashDriver::EFCError
FlashDriver::writeQuadWord(etl::array<uint32_t, WordsPerQuadWord> &data,
                           FlashAddress_t address) {
    if (not isAddressSafe(address)) {
        return EFCError::ADDRESS_UNSAFE;
    }

    const auto EraseResult = eraseSector(address);
    if (EraseResult != EFCError::NONE) {
        return EraseResult;
    }

    fseek(fptr, address - StartAddress, SEEK_SET);
    size_t bytes = fwrite(data.data(), 4, data.size(), fptr);
    if (bytes != data.size()) {
        LOG_ERROR << "  [QEMU] Failed to write to MCU_FLASH. Wrote " << bytes
                      << " bytes instead of " <<  data.size();
        return EFCError::FLASH_ERROR;
    }
}

[[nodiscard]] FlashDriver::EFCError
FlashDriver::writePage(etl::array<uint32_t, WordsPerPage> &data,
                       FlashAddress_t address) {
    if (not isAddressSafe(address)) {
        return EFCError::ADDRESS_UNSAFE;
    }

    const auto EraseResult = eraseSector(address);
    if (EraseResult != EFCError::NONE) {
        return EraseResult;
    }

    fseek(fptr, address - StartAddress, SEEK_SET);
    size_t bytes = fwrite(data.data(), 4, data.size(), fptr);
    if (bytes != data.size()) {
        LOG_ERROR << "  [QEMU] Failed to write to MCU_FLASH. Wrote " << bytes
                      << " bytes instead of " <<  data.size();
        return EFCError::FLASH_ERROR;
    }
}
