class Noncopyable
{
protected:
	// ensure the class cannot be constructed directly
	Noncopyable() {}
	// the class should not be used polymorphically
	~Noncopyable() {}
private:
	Noncopyable(const Noncopyable&);
	Noncopyable& operator=(const Noncopyable&);
};