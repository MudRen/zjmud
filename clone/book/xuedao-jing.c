// xuedao-jing.c

inherit ITEM;

void create()
{
	set_name("Ѫ��ħ��", ({ "xuedao jing", "jing" }));
	set_weight(200);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "��");
		set("long","����һ��������˿֯С���ӣ�����д��Ѫ��������С�֡�\n");
		set("no_sell", 1);
		set("material", "silk");
		set("skill", ([
			"name": "xuehai-mogong",//name of the skill
			"exp_required": 50000,  //minimum combat experience required
			"jing_cost": 45,	// jing cost every time study this
			"difficulty": 30,       // the base int to learn this skill
			"max_skill": 150,       // the maximum level you can learn
			"min_skill": 40,	// the minimum level you can learn
		]) );
	}
}
