// npcd.c

#pragma optimize
#pragma save_binary

#include <command.h>
#include <npc/name.h>
#include <npc/chinese.c>
#include <npc/japanese.c>
#include <npc/european.c>
#include <npc/masia.c>
#include <npc/indian.c>

#define HUANG_SHANG	     "/kungfu/class/ultra/huang"
#define DUGU_QIUBAI	     "/kungfu/class/ultra/dugu"
#define KUIHUA_TAIJIAN	  "/kungfu/class/ultra/kuihua"
#define NANHAI_SHENNI	   "/kungfu/class/ultra/shenni"

mapping levels = ([
//      combat_exp   skill_level
	50000      : 60,		// level 1
	100000     : 80,		// level 2
	200000     : 100,	       // level 3
	400000     : 125,	       // level 4
	800000     : 150,	       // level 5
	1200000    : 175,	       // level 6
	1600000    : 200,	       // level 7
	2000000    : 225,	       // level 8
	2500000    : 250,	       // level 9
	2700000    : 275,	       // level 10
	3000000    : 300,	       // level 11
	5000000    : 350,	       // level 12
	7500000    : 400,	       // level 13
	9000000    : 450,	       // level 14
	12000000   : 500,	       // level 15
	16000000   : 550,	       // level 16
	21000000   : 600,	       // level 17
	27000000   : 650,	       // level 18
	34000000   : 700,	       // level 19
	40000000   : 750,	       // level 20
	50000000   : 800,	       // level 21
	61000000   : 850,	       // level 22
	72000000   : 900,	       // level 23
	85000000   : 950,	       // level 24
]);

mapping place = ([
	"��ɽ����" : ({ "/d/huashan/pingxinshi", "/d/village/square",
			"/d/village/wexit", }),
	"���ݳ�"   : ({ "/d/city/beimen", "/d/city/nanmen",
			"/d/city/ximen", "/d/city/dongmen", }),
	"������"   : ({ "/d/changan/dong-chengmen", "/d/changan/nan-chengmen",
			"/d/changan/xi-chengmen", "/d/changan/bei-chengmen",
			"/d/changan/qinglong2", "/d/changan/baihu2", }),
	"�书��"   : ({ "/d/quanzhen/xijie", "/d/quanzhen/nanjie", }),
	"��ɽһ��" : ({ "/d/foshan/street1", "/d/foshan/southgate", }),
	"�Ϻ�һ��" : ({ "/d/xiakedao/xkroad4" }),
	"����һ��" : ({ "/d/shaolin/ruzhou" }),
	"��ɽһ��" : ({ "/d/songshan/tianzhongge", "/d/shaolin/shijie1",
			"/d/shaolin/shijie8", }),
	"����ɽ"   : ({ "/d/quanzhen/shanlu1", "/d/quanzhen/shijie1",
			"/d/quanzhen/shijie9", "/d/quanzhen/cuipinggu",
			"/d/quanzhen/baishulin3", "/d/gumu/taiyi1",
			"/d/gumu/shenheyuan", "/d/quanzhen/banshanting", }),
	"�ɶ���"   : ({ "/d/city3/southroad1", "/d/city3/qingyanggong",
			"/d/city3/northroad2", }),
	"���޺�"   : ({ "/d/xingxiu/tianroad2", }),
	"��ɽ"     : ({ "/d/lingjiu/yan", }),
	"���ݳ�"   : ({ "/d/suzhou/xidajie2", "/d/suzhou/dongdajie2",
			"/d/suzhou/road5", "/d/suzhou/road1",
			"/d/suzhou/gumujiaohe", "/d/suzhou/zhenquting", }),
	"���ݳ�"   : ({ "/d/hangzhou/suti2", "/d/hangzhou/jujingyuan",
			"/d/hangzhou/liuzhuang", "/d/hangzhou/road19",
			"/d/hangzhou/huangniling", "/d/hangzhou/qinglindong", }),
	"������"   : ({ "/d/xiangyang/westjie2", "/d/xiangyang/southjie2",
			"/d/xiangyang/xiaorong1", "/d/xiangyang/zhonglie",
			"/d/xiangyang/guangchang", "/d/xiangyang/dingzi", }),
	"Ȫ�ݳ�"   : ({ "/d/quanzhou/zhongxin", }),
	"���ݳ�"   : ({ "/d/fuzhou/ximendajie", "/d/fuzhou/dongxiaojie",
			"/d/fuzhou/nanmen", }),
	"����"     : ({ "/d/lingzhou/xidajie", "/d/lingzhou/nanmen",
			"/d/lingzhou/dongdajie", }),
	"����"     : ({ "/d/guanwai/baihe", "/d/guanwai/road8",
			"/d/guanwai/xuedi1", "/d/guanwai/beicheng",
			"/d/guanwai/shanshenmiao" }),
	"����"     : ({ "/d/xingxiu/shamo5", "/d/baituo/gebi",
			"/d/xueshan/shenghu", "/d/xueshan/hubian4",
			"/d/xuedao/sroad3", "/d/xuedao/nroad6",
			"/d/mingjiao/gebitan5",
			"/d/xingxiu/nanjiang2" }),
	"����һ��" : ({ "/d/dali/northgate", "/d/dali/southgate",
			"/d/dali/shanlu2", "/d/dali/buxiongbu",
			"/d/dali/jinzhihe", "/d/dali/xiaodao1",
			"/d/dali/tianweijing", "/d/dali/wuding",
			"/d/dali/luwang", "/d/dali/gudao",
			"/d/dali/biluoxueshan", "/d/dali/zhenxiong",
			"/d/dali/yixibu", "/d/dali/cangshanzhong",
			"/d/dali/wumeng", "/d/dali/hongsheng", }),
]);

// return the character(ob) 's level, 0 is lowest
int check_level(object ob)
{
	int *exp;
	int i;

	exp = sort_array(keys(levels), 1);
	for (i = 0; i < sizeof(exp); i++)
		if (ob->query("combat_exp") < exp[i]) break;
	return i;
}

// set the the level of the npc's skill
void init_npc_skill(object ob, int lvl)
{
	int sk_lvl;
	string *ks;
	int i;
	int exp;

	if (lvl < 1) lvl = 1;
	if (lvl >= sizeof(levels)) lvl = sizeof(levels) - 1;

	exp = sort_array(keys(levels), 1)[lvl - 1];
	ob->set("combat_exp", exp);
	sk_lvl = levels[exp];
	if (! ob->query_skills())
		return;
	ks = keys(ob->query_skills());
	for (i = 0; i < sizeof(ks); i++)
		ob->set_skill(ks[i], sk_lvl);
}

string *nations = ({ "�й�", "�ձ�", "���", "����", "����", "�ɹ�",
		     "����˹", "Ӣ����", "������", "������", "������",
		     "����ʱ", "������˹̹", "��ɳ��˹̹", "���ȱ��˹̹" });

// generate a npc with nation & skill level
object create_npc(string nation, int lvl)
{
	object ob;

	switch (nation)
	{
	case "�й�":
		ob = new(CLASS_D("generate") + "/chinese");
		NPC_D->generate_cn_name(ob);
		break;
	case "�ձ�":
		ob = new(CLASS_D("generate") + "/japanese");
		NPC_D->generate_jp_name(ob);
		break;
	case "Ӣ����":
	case "������":
	case "������":
	case "������":
	case "����ʱ":
	case "����":
		ob = new(CLASS_D("generate") + "/european");
		NPC_D->generate_e_name(ob);
		break;
	case "����":
		ob = new(CLASS_D("generate") + "/indian");
		NPC_D->generate_in_name(ob);
		break;
	case "������ģ":
	case "���":
	case "����˹":
	case "������˹̹":
	case "��ɳ��˹̹":
	case "���ȱ��˹̹":
	case "�ɹ�":
		return 0;
	}

	ob->set("nation", nation);
	init_npc_skill(ob, lvl);

	return ob;
}

// generate challenger
object create_challenger()
{
	string *n;
	object *ob;
	int max_level;
	int i;
	int lvl;

	ob = all_interactive();
	max_level = 0;
	for (i = 0; i < sizeof(ob); i++)
		if (! wizardp(ob[i]) && max_level < check_level(ob[i]))
			max_level = check_level(ob[i]);

	max_level++;
	lvl = 1 + random(max_level);
	if (lvl < 3) lvl = max_level;

	n = ({ "�ձ�", "�ձ�", "�ձ�",
	       "����",
	       "Ӣ����", "������", "������", "������", "����ʱ", "����", });
	return create_npc(n[random(sizeof(n))], lvl);
}

// set the basic parameter from me
void set_from_me(object tob, object fob, int scale)
{
	mapping my, hp_status;
	int s, max_qi;

	hp_status = fob->query_entire_dbase();
	my = tob->query_entire_dbase();

	if (! scale)
	{
		if (undefinedp(my["scale"]))
			my["scale"] = 100;
		scale = my["scale"];
	}

	my["str"] = hp_status["str"] * scale / 100;
	my["int"] = hp_status["int"] * scale / 100;
	my["con"] = hp_status["con"] * scale / 100;
	my["dex"] = hp_status["dex"] * scale / 100;

	// ���������Ѫ
	s = fob->query_con() + fob->query_str();
	max_qi = 100;
	
	if (hp_status["age"] < 14)
		max_qi = 60 + hp_status["age"] * hp_status["con"] / 2;
	else
	if (hp_status["age"] < 27)
		max_qi += (hp_status["age"] - 14) * s * 2 / 3;
	else
		max_qi += (hp_status["age"] - 14) * s;

	max_qi += (int)hp_status["max_neili"] / 4;		

	if (hp_status["breakup"])
		max_qi += max_qi;
		
	max_qi = max_qi   * scale / 100;		

	my["max_qi"]     = max_qi;
	my["eff_qi"]     = my["max_qi"];
	my["qi"]	 = my["max_qi"];
	my["max_jing"]   = hp_status["max_jing"] * scale / 100;
	my["eff_jing"]   = my["max_jing"];
	my["jing"]       = my["max_jing"];
	my["max_neili"]  = hp_status["max_neili"]* scale / 100;
	
	if (hp_status["combat_exp"] > 800000)
	{
		my["jiali"] = tob->query_skill("force") / 3;
	}
	else
	{
		my["jiali"] = tob->query_skill("force") / 6;
	}
	
	if (my["max_neili"] > 9000)
		my["max_neili"] = 9000;

	my["neili"]      = my["max_neili"] * 2;

	tob->set_from_me(fob, scale);
}

// select a random place
string random_place(string *not_place)
{
	string *kp;

	kp = keys(place);

	// exclude some place
	if (arrayp(not_place))
		kp -= not_place;

	// select a random place
	return kp[random(sizeof(kp))];
}

// place npc
void place_npc(object ob, string *not_place, string *in_place)
{
	string *kp;
	string p;
	string startroom;
	object pos;

	// select the place
	if (! arrayp(in_place))
		kp = keys(place);
	else
		kp = in_place;

	// exclude some place
	if (arrayp(not_place))
		kp -= not_place;

	// select the exact position
	for (;;)
	{
		p = kp[random(sizeof(kp))];
		startroom = place[p][random(sizeof(place[p]))];
		if (! objectp(pos = get_object(startroom)))
		{
			log_file("log", sprintf("error to place npc to %s:%s\n",
						p, startroom));
			continue;
		}
		break;
	}

	// move to the position
	ob->move(pos);
	ob->set("place", p);
	ob->set("startroom", startroom);
	ob->set_temp("moved", ({ }));
	message_vision("$N���˹�����\n", ob);
}

#define MAX_MOVED       2

// random move
void random_move(object ob)
{
	mapping exits;
	string *moved;
	string dir;
	string *dirs;
	int i;

	moved = ob->query_temp("moved");
	if (! moved) moved = ({ });
	if (sizeof(moved) >= MAX_MOVED)
	{
		// out of range, move back
		dir = GO_CMD->query_reverse(moved[sizeof(moved) - 1]);
	} else
	{
		exits = environment(ob)->query("exits");
		dirs = keys(exits);
		for (i = 0; i < 12; i++)
		{
			if (! sizeof(dirs))
				return;
			dir = dirs[random(sizeof(dirs))];
			if (stringp(GO_CMD->query_reverse(dir)) &&
			    ! exits[dir]->query("no_fight"))
				break;
			dirs -= ({ dir });
		}
	}

	if (sizeof(moved) &&
	    GO_CMD->query_reverse(dir) == moved[sizeof(moved) - 1])
	{
		// move back
		moved = moved[0..<2];
	} else
		moved += ({ dir });
	ob->set_temp("moved", moved);

	GO_CMD->main(ob, dir);
}

// get all ultra master
object *query_ultra_master()
{
	return ({ get_object(HUANG_SHANG),
		  get_object(DUGU_QIUBAI),
		  get_object(KUIHUA_TAIJIAN),
		  get_object(NANHAI_SHENNI) });
}


