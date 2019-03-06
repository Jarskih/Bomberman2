#include "Sprite.h"
#include "SpriteHandler.h"
#include "Service.h"
#include "Collider.h"
#include "Config.h"
#include "Block.h"
#include <iostream>
#include "Flame.h"

Block::Block(const char* p_textureFilePath, int p_srcX, int p_srcY, int p_srcW, int p_srcH, int p_colliderX,
	int p_colliderY, int p_colliderW, int p_colliderH, int p_x, int p_y, int p_block_type, bool p_has_collider)
{
	m_block_type = p_block_type;
	m_type = BLOCK;
	m_x = p_x;
	m_y = p_y;
	m_spriteBlock = Service<SpriteHandler>::Get()->CreateSprite(p_textureFilePath, p_srcX, p_srcY, p_srcW, p_srcH);
	m_spriteGrass = Service<SpriteHandler>::Get()->CreateSprite("img/grass.png", p_srcX, p_srcY, p_srcW, p_srcH);
	m_spriteSheet = Service<SpriteHandler>::Get()->CreateSpriteSheet("img/block_breaking.png", p_srcX, p_srcY, p_srcW,
		p_srcH, 7);
	m_sprite = m_spriteBlock;
	m_frame = 0;
	m_delayPerFrame = 100;
	m_exploded = false;
	m_window_rect = { m_x, m_y, Config::BLOCK_WIDTH, Config::BLOCK_HEIGHT };
	if (p_has_collider)
	{
		m_collider = new RectangleCollider(p_colliderX, p_colliderY, p_colliderW, p_colliderH);
		m_collider->SetPosition(m_x, m_y);
	}
	else
	{
		m_collider = new RectangleCollider(0, 0, 0, 0);
	}
}

Block::~Block()
{
	m_collider = nullptr;
}

void Block::Render(SDL_Renderer* p_renderer)
{
	if (m_block_type == Config::Blocks::GRASS)
	{
		SDL_Rect dst = { m_x, m_y, m_sprite->GetArea().w, m_sprite->GetArea().h };
		SDL_RenderCopy(p_renderer, m_sprite->GetTexture(), &m_sprite->GetArea(), &dst);
	}
	else if (m_exploded)
	{
		if (animator.PlayOnce(p_renderer, *m_spriteSheet, m_delayPerFrame, m_window_rect, m_timeExploded))
		{
			changeBlockType(Config::GRASS);
		}
	}
	else
	{
		SDL_Rect dst = { m_x, m_y, m_sprite->GetArea().w, m_sprite->GetArea().h };
		SDL_RenderCopy(p_renderer, m_sprite->GetTexture(), &m_sprite->GetArea(), &dst);
	}
}

void Block::Update()
{
	if (m_exploded)
	{
		m_collider = new RectangleCollider(0, 0, 0, 0);
		m_sprite = m_spriteGrass;
	}
}

std::pair<int, int> Block::getBlockIndex() const
{
	return Helpers::GetCurrentBlock(m_x, m_y);
}

void Block::OnCollision(sp<Flame> &flame)
{
	if (flame->GetType() == FLAME)
	{
		setDestroyed();
	}
}

int Block::gCost() const
{
	return m_g_cost;
}

int Block::hCost() const
{
	return m_h_cost;
}

int Block::fCost() const
{
	return m_g_cost + m_h_cost;
}

void Block::SetHCost(int h_cost)
{
	m_h_cost = h_cost;
}

void Block::SetGCost(int g_cost)
{
	m_g_cost = g_cost;
}

int Block::GetIndexX() const
{
	return m_index_x;
}

int Block::GetIndexY() const
{
	return m_index_y;
}

int Block::GetBlockType() const
{
	return m_block_type;
}

void Block::SetParent(Block& block)
{
	m_parent = &block;
}

Block* Block::GetParent() const
{
	return m_parent;
}

void Block::setDestroyed()
{
	if (m_block_type != Config::Blocks::DESTROYED)
	{
		m_timeExploded = SDL_GetTicks();
		m_exploded = true;
		m_block_type = Config::Blocks::DESTROYED;
	}
}

void Block::changeBlockType(int newType)
{
	if (m_block_type != newType)
	{
		m_block_type = newType;
	}
}
