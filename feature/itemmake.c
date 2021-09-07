// itemmake.c ���Ƶ���

#include <dbase.h>
#include <ansi.h>
#include <name.h>
#include <move.h>
#include <command.h>

inherit F_OBSAVE;
inherit F_NOCLONE;
int weapon_level();

int is_item_make() { return 1; }

#define	LEVEL1		50
#define	LEVEL2		500
#define	LEVEL3		1000
#define	LEVEL4		3000
#define	LEVEL5		6000
#define	LEVEL6		10000
#define	LEVEL7		15000
#define	LEVEL8		20000
#define	LEVEL9		25000
#define MAX_LEVEL       LEVEL9
#define ULTRA_LEVEL     (LEVEL9 + 10)

static int *levels = ({ LEVEL1, LEVEL2, LEVEL3, LEVEL4,
			LEVEL5, LEVEL6, LEVEL7, LEVEL8,
			LEVEL9, ULTRA_LEVEL });

static int performing  = 0;
static int attack_lvl  = 0;
static int defense_lvl = 0;

int is_stay_in_room() { return attack_lvl >= ULTRA_LEVEL; }
int level_max_exp(int level)
{
	int lvl,attack_lvl;

	attack_lvl = weapon_level();
	lvl = sizeof(levels);

	while (--lvl)
		if (attack_lvl >= levels[lvl])
			break;
	lvl++;
	if(lvl>9) lvl = 9;
	return levels[lvl];
}
int level_now(int level)
{
	int lvl,attack_lvl;

	attack_lvl = weapon_level();
	lvl = sizeof(levels);

	while (--lvl)
		if (attack_lvl >= levels[lvl])
			break;
	lvl++;
	return lvl;
}
// ����������ID - ͨ���ļ����������ж�
string item_owner()
{
	string owner;
	if (sscanf(base_name(this_object()), ITEM_DIR "%*s/%s-%*s", owner))
		return owner;

	return 0;
}

// �жϸ������Ƿ񱻵�ǰĳ��������
int is_not_belong_me(object me)
{
	string user;

	user = query("user");
	if (! user || ! sscanf(user, "%*s(" + me->query("id") + ")"))
		return 1;

	return 0;
}

// ����װ���ĵȼ�
int weapon_level()
{
	mapping o;
	string *ks;
	int lvl;
	int i;

	lvl = 0;
	o = query("owner");
	if (mapp(o))
	{
		ks = keys(o);
		for (i = 0; i < sizeof(ks); i++)
			lvl += o[ks[i]];
	}

	lvl /= 100;
	if (lvl > MAX_LEVEL) lvl = MAX_LEVEL;

	if (lvl == MAX_LEVEL && query("magic/power"))
		// ����ħ������
		lvl = ULTRA_LEVEL;
	return lvl;
}

int weapon_exp()
{
   mapping o;
	string *ks;
	int lvl_exp;
	int i;

	lvl_exp = 0;
	o = query("owner");
	if (mapp(o))
	{
		ks = keys(o);
		for (i = 0; i < sizeof(ks); i++)
			lvl_exp += o[ks[i]];
	}
     return lvl_exp/100;
}
// ����װ���ĵȼ�
int armor_level()
{
	mapping o;
	string *ks;
	int lvl;
	int i;

	lvl = 0;
	o = query("owner");
	if (mapp(o))
	{
		ks = keys(o);
		for (i = 0; i < sizeof(ks); i++)
			lvl += o[ks[i]];
	}

	lvl /= 100;
	if (lvl > MAX_LEVEL) lvl = MAX_LEVEL;

	if (lvl == MAX_LEVEL && query("magic/power"))
		// ����ħ������
		lvl = ULTRA_LEVEL;
	return lvl;
}
int armor_exp()
{
   mapping o;
	string *ks;
	int lvl_exp;
	int i;

	lvl_exp = 0;
	o = query("owner");
	if (mapp(o))
	{
		ks = keys(o);
		for (i = 0; i < sizeof(ks); i++)
			lvl_exp += o[ks[i]];
	}
     return lvl_exp/100;
}

// ����װ���ĳ�����
string weapon_long()
{
	string  n;
	mapping c;
	int type;
	int k;
	int lvl;
	string tessera_name;
	string result;

	c = query("combat");
	n = query("unit") + name();
	if (! c)
		return "��" + n + "��Ȼ��û��������Ѫ�����洿����Ͼ��\n";
	k = c["MKS"] + c["PKS"];

	if (c["WPK_GOOD"] < k / 2 &&
	    c["WPK_BAD"]  < k / 2)
		type = 0;
	else
	if (c["WPK_GOOD"] > c["WPK_BAD"] * 2)
		type = -1;
	else
		type = 1;

	if (c["MKS"] + c["PKS"] < 10)
		return "��" + n + "�����Ѿ��ù���Ѫ��������������Ѫ�ۡ�\n";

	attack_lvl = weapon_level();
	lvl = sizeof(levels);
	while (--lvl)
		if (attack_lvl >= levels[lvl])
			break;
	lvl++;

	switch (type)
	{
	case 1:
		if (attack_lvl >= ULTRA_LEVEL)
			result = HIY "������ȥƽƽ������û�а�����⣬ֻ��"
				 "���������˸е��ǲ��������ʡ�"NOR"\n";
		else
		if (attack_lvl >= MAX_LEVEL)
			result = HIY "������ȥ���˷����������޳羴��һ��"
			       "�Ȼ������Ȼ���棬�ľߵ����緶������\n"
			       "���£�������·�����ɷ���ѵ�����Ǵ�˵�в�"
			       "����ֵ�����֮" + name() + HIY "��"NOR"\n";
		else
		if (attack_lvl >= LEVEL8)
			result = HIC "һ����ȥ��������������������ڷ��"
			       "���裬�������أ�����֮�����ƺ�Ҫ�ط�\n"
			       "�˼䡣���̲�סҪ��̾һ����������ħ��Ҳ�������١�"NOR"\n";
		else
		if (attack_lvl >= LEVEL7)
			result = HIC "�����渽���Ų�֪�����׻꣬����а��"
			       "��ħ�������£�һ�ɰ�����Ȼ��ɢ������\n"
			       "�̲�ס���˸���ս��"NOR"\n";
		else
		if (attack_lvl >= LEVEL6)
			result = HIR "������ȥ���˾��Ķ��ǣ����������������" + name() + HIR
			       "��������ɷ�ʹ˱������ɾ��˼����塣"NOR"\n";
		else
		if (attack_lvl >= LEVEL5)
			result = HIR "����������Ȼ͸��һ��Ѫ�⣬�������������"
			       "����������һʱ����ħ������" + name() + HIR "�µ��λꡣ"NOR"\n";
		else
		if (attack_lvl >= LEVEL4)
			result = HIW "����ǽ��������������֮һ��" + name() + HIW
			       "�����׼���֮ͽ�������޲��ĳ���ҡ��"NOR"\n";
		else
		if (attack_lvl >= LEVEL3)
			result = HIW "��" + n + HIW "��һ������ɢ�������������������׻겻�١�"NOR"\n";
		else
		if (attack_lvl >= LEVEL2)
			result = RED "��" + n + RED "��Ȼ͸��һ��������"
			       "������ɱ�˲����׶�֮ͽ��"NOR"\n";
		else
		if (attack_lvl >= LEVEL1)
			result = RED "ϸ��֮�£��п���һ˿Ѫ�ۣ��������ɱ�˲���"
			       "����Ѫ�ڴ˰ɣ�"NOR"\n";
		else
			result = CYN "���ó���" + n + CYN "����ɱ�������׶�֮ͽ��"NOR"\n";
		break;

	case -1:
		if (attack_lvl >= ULTRA_LEVEL)
			result = HIR "������ȥƽƽ������û�а�����⣬����"
				 "��֪Ϊ��ȴ�������˸е���Щ������"NOR"\n";
		else
		if (attack_lvl >= MAX_LEVEL)
			result = HIR "������ȥ���˴��ĵ׷��������⣬��"
			       "��Ȼ�����ƺ�����������ԩ�꣬����ȫȻ\n����" + n + HIR
			       "�����ɱ�����ƣ��ѵ�����Ǵ�˵�вŻ���ֵ�а��֮" + name() + HIR
			       "��"NOR"\n";
		else
		if (attack_lvl >= LEVEL8)
			result = HIC "һ����ȥ���������������ԩ��������"
			       "�����������أ�����֮�������̲�ס����\n"
			       "����ս�������ٿ��ڶ��ۡ�"NOR"\n";
		else
		if (attack_lvl >= LEVEL7)
			result = HIC "�����渽���Ų�֪����ԩ�꣬��������"
			       "�������£�һ��Թ��ֱ�������������̲�\n"
			       "ס���˸���ս��"NOR"\n";
		else
		if (attack_lvl >= LEVEL6)
			result = HIW "������ȥ���˾��Ķ��ǣ����������������" + name() + HIW
			       "����֪����Ӣ�۾ʹ����ޡ�"NOR"\n";
		else
		if (attack_lvl >= LEVEL5)
			result = HIW "����������Ȼ͸��һ��Ѫ�⣬�������������"
			       "����������һʱ�ĸ��ֶ�����" + name() + HIW "�µ��λꡣ"NOR"\n";
		else
		if (attack_lvl >= LEVEL4)
			result = HIG "����ǽ���������������֮һ��" + name() + HIG
			       "��˭������ô��������ʿ�������¡�"NOR"\n";
		else
		if (attack_lvl >= LEVEL3)
			result = HIG "��һ������ɢ�������������������λ겻�١�"NOR"\n";
		else
		if (attack_lvl >= LEVEL2)
			result = RED "��Ȼ͸��һ��������������ɱ�˲����ˡ�"NOR"\n";
		else
		if (attack_lvl >= LEVEL1)
			result = RED "ϸ��֮�£��п���һ˿Ѫ�ۣ��������ɱ�˲���"
			       "����Ѫ�ڴ˰ɣ�"NOR"\n";
		else
			result = CYN "���ó���" + n + CYN "����ɱ����������֮ʿ��"NOR"\n";
		break;

	default:
		if (attack_lvl >= ULTRA_LEVEL)
			result = HIC "������ȥƽƽ������û�а�����⣬ֻ��һ��"
				 "ƽ��֮���ı������ѡ�"NOR"\n";
		else
		if (attack_lvl >= MAX_LEVEL)
			result = HIC "����Ȼ���⣬�ƺ���Ҫ�ڿն�ȥ������"
			       "���磬�������С���������·������\n"
			       "��������֮����ԩ�겻�衢Ⱥа���ף��޲�����" + n + HIC
			       "�Ϲ�����İ������ơ�"NOR"\n";
		else
		if (attack_lvl >= LEVEL8)
			result = HIM "һ����ȥ����������������λ�������"
			       "�����������أ�����֮�������ʱ������\n"
			       "�����ޱȣ���������ס��"NOR"\n";
		else
		if (attack_lvl >= LEVEL7)
			result = HIM "�����渽���Ų�֪�����λ꣬������а"
			       "����ɥ�����£�һ��Թ��������Ȼ������\n"
			       "�����̲�ס���˸���ս��"NOR"\n";
		else
		if (attack_lvl >= LEVEL6)
			result = HIR "������ȥ���˾��Ķ��ǣ����������������" + name() + HIR
			       "��������а���ֶ����Ӵ˽٣������ֻء�"NOR"\n";
		else
		if (attack_lvl >= LEVEL5)
			result = HIR "����������Ȼ͸��һ��Ѫ�⣬�������������"
			       "����������һʱ�ĸ��ֶ�������" + n + HIR "�µ��λꡣ"NOR"\n";
		else
		if (attack_lvl >= LEVEL4)
			result = HIW "����ǽ���������������֮һ��" + name() + HIW
			       "��˭���뵽��ô������������¡�"NOR"\n";
		else
		if (attack_lvl >= LEVEL3)
			result = HIW "��" + n + HIW "��һ��ɱ��ɢ�������������������λ겻�١�"NOR"\n";

		else
		if (attack_lvl >= LEVEL2)
			result = RED "��" + n + RED "��Ȼ͸��һ��ɱ����������ɱ�˲����ˡ�"NOR"\n";

		else
		if (attack_lvl >= LEVEL1)
			result = RED "ϸ��֮�£��п���һ˿Ѫ�ۣ��������ɱ�˲���"
			       "����Ѫ�ڴ˰ɣ�"NOR"\n";
		else
			result = CYN "���ó���" + n + CYN "����ɱ�������ˡ�"NOR"\n";
		break;
	}

	if (query("magic"))
	{
		result += HIY + name() + HIY "�ĵȼ���" + lvl + "/9"NOR"\n";
		if (stringp(tessera_name = query("magic/tessera")))
			result += "��������Ƕ��" + tessera_name + "����˸������Ĺ�â��\n";
	} else
	if (lvl)
	{
		result += HIY + name() + HIY "�ĵȼ���" + lvl + "/9"NOR"\n";

		if (query("magic/imbue_ok"))
			result += HIM + name() + HIM "�Ѿ���ֵĽ����ˣ���Ҫ"
				  "��Ƕ�Գ�ַ���������"NOR"\n";
		else
		if ((n = query("magic/imbue")) > 0)
			result += HIM + name() + HIM "�Ѿ��������������" +
				  chinese_number(n) + "�Σ����ڼ�������Ǳ�ܡ�"NOR"\n";
	}

	return result;
}

// ����ͨ����װ��
int is_weapon()
{
	return stringp(query("skill_type"));
}

// �ǿ�������װ��
int is_unarmed_weapon()
{
	return query("armor_type") == "hands";
}

// ���ߵĳ�����
string item_long()
{
	if (is_weapon() || is_unarmed_weapon())
		return weapon_long();

	return "";
}

// ����װ�����˺�ֵ
int apply_damage()
{
	int d;
	int p;

	attack_lvl = weapon_level();
	p = query("point") / 2;
	d = attack_lvl * p / MAX_LEVEL;
	return d + p;
}

// ����װ������Чֵ
int apply_armor()
{
	int d;
	int p;

	defense_lvl = armor_level();
	p = query("point");
	d = defense_lvl * p / MAX_LEVEL;
	return d + p;
}

// ���б������ݵĽӿں���
mixed save_dbase_data()
{
	mapping data;
	object  user;

	data = ([ "combat" : query("combat"),
		  "owner"  : query("owner"),
		  "magic"  : query("magic"),
		  "consistence" : query("consistence"), ]);

	if (! (user = environment()))
		data += ([ "user" : query("user") ]);
	else
	if (playerp(user))
		data += ([ "user" : user->name(1) + "(" + user->query("id") + ")" ]);

	return data;
}

// ���ܴ������ݵĽӿں���
int receive_dbase_data(mixed data)
{
	if (! mapp(data))
		return 0;

	if (mapp(data["combat"]))
		set("combat", data["combat"]);

	if (mapp(data["owner"]))
		set("owner", data["owner"]);

	if (mapp(data["magic"]))
		set("magic", data["magic"]);

	if (stringp(data["user"]))
		set("user", data["user"]);

	if (! undefinedp(data["consistence"]))
		set("consistence", data["consistence"]);

	return 1;
}

// ��ȡ���̵�����
int restore()
{
	int r;

	if (base_name(this_object()) + ".c" == __FILE__)
		return 0;

	r = ::restore();
	set("no_sell", 1);
	return r;
}

// ��������
int save()
{
	int res;

	if (base_name(this_object()) + ".c" == __FILE__)
		return 0;

	return ::save();
}

// ħ��Ч����������
mixed weapon_hit_ob(object me, object victim, int damage_bonus)
{
	int ap;
	int dp;
	int damage;

	if (item_owner() != me->query("id"))
		return;

	if (query("magic/power"))
	{
		return ITEM_D->weapon10lv_hit_ob(me, victim, this_object(), damage_bonus);
	}

	return;
}

// ���µĺ�����Ϊִ�е�Ƶ�Ȳ����ߣ����Ҿ��и߶��ظ������ʣ�
// ���Զ�����ITEM_D�е�ִ�г���

// ɱ�����Ժ�Ľ���
void killer_reward(object me, object victim)
{
	ITEM_D->killer_reward(me, victim, this_object());
}

// ������Ʒ
int receive_summon(object me)
{
	return ITEM_D->receive_summon(me, this_object());
}

// ������Ʒ
int hide_anywhere(object me)
{
	return ITEM_D->hide_anywhere(me, this_object());
}

// ׷Ѱ��Ʒ
int receive_miss(object me)
{
	if (! is_weapon() && ! is_unarmed_weapon())
	{
		write("���޷�׷Ѱ" + name() + "��\n");
		return 0;
	}

	if (attack_lvl < ULTRA_LEVEL)
	{
		write(name() + "��δͨ�飬����������ĸ�Ӧ��\n");
		return 0;
	}

	return ITEM_D->receive_miss(me, this_object());
}

// ���ڵ���
int do_stab(object me)
{
	return ITEM_D->do_stab(me, this_object());
}

// ��������
int do_touch(object me)
{
	if (attack_lvl != ULTRA_LEVEL)
		return notify_fail("�����˰��죬����ûʲô��Ӧ��\n");

	return ITEM_D->do_touch(me, this_object());
}

// ʥ��
int do_san(object me)
{
//	if ((is_weapon() || is_unarmed_weapon()) && attack_lvl < MAX_LEVEL)
//		return notify_fail("��������ȼ��������޷�ʥ����\n");

	return ITEM_D->do_san(me, this_object());
}

// ��͸��Ʒ
int do_imbue(object me)
{
	return ITEM_D->do_imbue(me, this_object());
}

// ��Ƕ��Ʒ
int do_enchase(object me, object tessera)
{
	return ITEM_D->do_enchase(me, this_object(), tessera);
}

// ǿ����Ʒ
int do_enhance(object me, object tessera)
{
	return ITEM_D->do_enhance(me, this_object(), tessera);
}

int query_autoload() { return (query("equipped") ? query("equipped") : "kept"); }

void autoload(string parameter)
{
	switch (parameter)
	{
	case "worn":
		this_object()->wear();
		break;

	case "wielded":
		this_object()->wield();
		break;
	}
}

void owner_death_penalty()
{
	object item = this_object();

	if (item->add("consistence", -20) < 0)
	{
		item->set("consistence", 0);
		if (environment(item))
			tell_object(environment(item), HIG "���" + item->name() + "�Ѿ��������ˡ�\n");
		item->unequip();
	}
}