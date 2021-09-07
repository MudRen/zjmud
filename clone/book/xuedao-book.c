// xuedao-book.c

inherit ITEM;

void create()
{
	set_name("Ѫ���ؼ�", ({ "xuedao book", "book" }));
	set_weight(200);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "��");
		set("long","����һ��������С���ӣ�����д��Ѫ���ؼ��ĸ�С�֡�\n");
		set("no_sell", 1);
		set("material", "silk");
		set("skill", ([
			"name": "xue-dao",      //name of the skill
			"exp_required": 100000, //minimum combat experience required
			"jing_cost": 50,	// jing cost every time study this
			"difficulty": 32,       // the base int to learn this skill
			"max_skill": 180,       // the maximum level you can learn
			"min_skill": 50,	// the minimum level you can learn
		]) );
	}
}
