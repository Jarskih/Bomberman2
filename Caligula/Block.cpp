#include "Sprite.h"
#include "SpriteHandler.h"
#include "Service.h"
#include "Collider.h"
#include "Config.h"
#include "Block.h"

Block::Block(const char* p_textureFilePath, int p_srcX, int p_srcY, int p_srcW, int p_srcH, int p_colliderX, int p_colliderY, int p_colliderW, int p_colliderH, int p_x, int p_y, int p_block_type, bool p_has_collider)
{
	m_block_type = p_block_type;
	m_type = BLOCK;
	m_x = p_x;
	m_y = p_y;
	m_sprite = Service<SpriteHandler>::Get()->CreateSprite(p_textureFilePath, p_srcX, p_srcY, p_srcW, p_srcH);
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

void Block::Render(SDL_Renderer* p_renderer) {
	SDL_Rect dst = { m_x, m_y, m_sprite->GetArea().w, m_sprite->GetArea().h };
	SDL_RenderCopy(p_renderer, m_sprite->GetTexture(), &m_sprite->GetArea(), &dst);

	SDL_SetRenderDrawColor(p_renderer, 0, 255, 0, 0);
	SDL_RenderDrawRect(p_renderer, &m_collider->GetBounds());

	/*
	if (m_old_block_type != m_block_type)
	{
		//LoadTexture();
		m_old_block_type = m_block_type;
	}

	m_window_rect.x = m_x;
	m_window_rect.y = m_y;
	m_collider.x = m_x;
	m_collider.y = m_y;

	const int totalFrames = 7;
	if (m_block_type == Config::DESTROYED)
	{
		if (m_block_has_power_up && !m_power_up_added) {
			auto map = Service<Map>::Get();
			map->addPowerUp(m_index_x, m_index_y, m_power_up_type);
			m_power_up_added = true;
		}

		const int delayPerFrame = 100;

		if (SDL_GetTicks() - timeExploded > delayPerFrame)
		{
			m_texture_rect.y = m_frame * m_texture_rect.h;
			SDL_QueryTexture(m_texture, nullptr, nullptr, &m_texture_rect.w, &m_texture_rect.h);

			m_texture_rect.h /= totalFrames;
			m_frame++;
		}
		if (m_frame >= totalFrames - 1)
		{
			changeBlockType(Config::GRASS);
		}
		SDL_RenderCopy(p_renderer, m_texture, &m_texture_rect, &m_window_rect);
	}
	else
	{
		SDL_RenderCopy(p_renderer, m_texture, nullptr, &m_window_rect);
	}
	*/
}

void Block::Update()
{
}

std::pair <int, int> Block::getBlockIndex() const
{
	return Helpers::GetCurrentBlock(m_x, m_y);
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

int Block::GetPositionX() const
{
	return m_x;
}

int Block::GetPositionY() const
{
	return m_y;
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

bool Block::HasPowerUp() const
{
	return m_block_has_power_up;
}

void Block::SpawnPowerUp(int powerUpType)
{
	m_block_has_power_up = true;
	m_power_up_type = powerUpType;
}

Block* Block::GetParent() const
{
	return m_parent;
}

std::string Block::getTexturePath() const
{
	std::string texturePath;
	switch (m_block_type) {
	case Config::BREAKABLE:
		texturePath = "img/block.png";
		break;
	case Config::NONBREAKABLE:
		texturePath = "img/whiteBlock.png";
		break;
	case Config::WALL_UP:
		texturePath = "img/wallTop.png";
		break;
	case Config::WALL_LEFT:
		texturePath = "img/wallLeft.png";
		break;
	case Config::WALL_RIGHT:
		texturePath = "img/wallRight.png";
		break;
	case Config::WALL_DOWN:
		texturePath = "img/wallDown.png";
		break;
	case Config::WALL_LEFT_UP:
		texturePath = "img/wallTopLeft.png";
		break;
	case Config::WALL_RIGHT_UP:
		texturePath = "img/wallTopRight.png";
		break;
	case Config::WALL_LEFT_DOWN:
		texturePath = "img/wallDown.png";
		break;
	case Config::WALL_RIGHT_DOWN:
		texturePath = "img/wallDown.png";
		break;
	case Config::GRASS:
		texturePath = "img/grass.png";
		break;
	case Config::DESTROYED:
		texturePath = "img/block_breaking.png";
		break;
	default:
		texturePath = "error";
		break;
	}

	return texturePath;
}
/*
void Block::LoadTexture() {
	switch (m_block_type) {
	case Config::BREAKABLE:
		m_texture = m_textures->findTexture("block");
		break;
	case Config::NONBREAKABLE:
		m_texture = m_textures->findTexture("whiteBlock");
		break;
	case Config::WALL_UP:
		m_texture = m_textures->findTexture("wallTop");
		break;
	case Config::WALL_LEFT:
		m_texture = m_textures->findTexture("wallLeft");
		break;
	case Config::WALL_RIGHT:
		m_texture = m_textures->findTexture("wallRight");
		break;
	case Config::WALL_DOWN:
		m_texture = m_textures->findTexture("wallDown");
		break;
	case Config::WALL_LEFT_UP:
		m_texture = m_textures->findTexture("wallTopLeft");
		break;
	case Config::WALL_RIGHT_UP:
		m_texture = m_textures->findTexture("wallTopRight");
		break;
	case Config::WALL_LEFT_DOWN:
		m_texture = m_textures->findTexture("wallDown");
		break;
	case Config::WALL_RIGHT_DOWN:
		m_texture = m_textures->findTexture("wallDown");
		break;
	case Config::GRASS:
		m_texture = m_textures->findTexture("grass");
		break;
	case Config::DESTROYED:
		m_texture = m_textures->findTexture("blockBreaking");
		break;
	default:
		break;
	}
}
*/

void Block::changeBlockType(int newType)
{
	m_block_type = newType;
	m_texture_loaded = false;
	timeExploded = SDL_GetTicks();
}
