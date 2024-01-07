-- local ParentClass = {}

-- ParentClass.__index = ParentClass

-- function ParentClass.new(init)
--   local self = setmetatable({}, ParentClass)

--   self.value = init

--   return self
-- end

-- function ParentClass.set_value(self, new_value)
--   self.value = new_value
-- end

-- function ParentClass:get_value()
--   return self.value
-- end

-- local instance = ParentClass.new(10)
-- print(instance:get_value())
-- instance.set_value(instance, 30)
-- print(instance.get_value(instance))


Car = {
  name="",
  color="",
  velocity=0,
  acceleration=0
}
Car.__index = Car

function Car:new(name, color)
  local self = setmetatable({}, Car)
  self.name = name
  self.color = color
  return self
end

function Car.print_name(self)
  print("Name: ", self.name)
end

function Car:print_color()
  print("Color: ", self.color)
end

function Car.print_velocity(self)
  print("Velocity: ", self.velocity)
end

function Car:print_acceleration()
  print("Acceleration: ", self.acceleration)
end

mustang = Car:new("mustang", "blue")
-- print all results
mustang:print_name()
mustang.print_color(mustang)
mustang.print_acceleration(mustang)
mustang:print_velocity()