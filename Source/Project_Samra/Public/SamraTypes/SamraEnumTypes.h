#pragma once

UENUM()
enum class ESamraConfirmType : uint8
{
	Yes,
	No
};

UENUM()
enum class ESamraValidType : uint8
{
	Valid,
	Invalid
};

UENUM()
enum class ESamraSuccessType : uint8
{
	Successful,
	Failed
};

UENUM()
enum class ESamraCountDownActionInput : uint8
{
	Start,
	Cancel
};

UENUM()
enum class ESamraCountDownActionOutput : uint8
{
	Updated,
	Completed,
	Canceled
};

UENUM()
enum class ESamraInputMode : uint8
{
	GameOnly,
	UIOnly,
	GameAndUIOnly
};