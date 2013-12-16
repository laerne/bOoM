#ifndef H_ImageEnitity
#define H_ImageEnitity
namespace bOoM {
namespace graphic {

using std::unique_ptr;
struct SingleImageEntity
{
public:
	SingleImageEntity() = default;
	void set_image(unique_ptr<Image>& image_ptr)
		{ the_image = std::move(image_ptr); }
	void set_image(Image&& image_ref)
		{ the_image.reset(&image_ref); }
	Image& image()
		{ return *the_image; }
	Image const& image() const
		{ return *the_image; }
protected:
	unique_ptr<Image> the_image;
};


template<int N>
struct StaticCyclicImageEntity
{
public:
	StaticCyclicImageEntity() = default;
	void set_image(size_t index, unique_ptr<Image>& image_ptr)
		{ images[index] = image_ptr; }
	void set_image(size_t index, Image&& image_ref)
		{ images[index].reset(image_ref); }
	Image& image(size_t index)
		{ return *images[index]; }
	Image const& image(size_t index) const
		{ return *images[index]; }
protected:
	unique_ptr<Image> images[N];
};

} //namespace graphic
} //namespace bOoM
#endif


