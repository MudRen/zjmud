//
//  ��Ƥ��

inherit ITEM;

void create()
{
	set_name( "��Ƥ����", ({ "skin" }));
	set_weight(200);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "��");
		set("long", "����һ����Ƥ�ʵصľ��ᣬ���滭��һЩ�Źֵķ��š�\n");
		set("material", "paper");
		set("skill", ([
			"name": "hammer",	// name of the skill
			"exp_required": 200000, // minimum combat experience required
			"jing_cost":    40,     // jing cost every time study this
			"difficulty":   40,     // the base int to learn this skill
			"max_skill":    150,    // the maximum level you can learn
			"min_skill":    20,     // the minimum level you can learn
		]) );
	}
}

