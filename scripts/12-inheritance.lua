Enemy = {
    health = 0
}
Enemy.__index = Enemy

function Enemy:new(health)
    local newEnemy = {}
    setmetatable(newEnemy, Enemy)
    newEnemy.health = health
    return newEnemy
end

function Enemy:printa()
    print("valor do health: "..self.health)
end

Boss = {}

setmetatable(Boss , {__index = Enemy})

function Boss:new(health)
    local newBoss = {}
    setmetatable(newBoss, Boss)
    self.health = health
    return self
end

function Boss:printa()
    print("to aqui")
end

boss = Boss:new(1000)
boss:printa()