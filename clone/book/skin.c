//
//  ��Ƥ��

inherit ITEM;

void create()
{
	set_name( "��Ƥ��", ({ "skin" , "shu", "book" }));
	set_weight(200);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "��");
		set("long", "����һ����Ƥ�����滭�ż����轣��С�ˡ�\n");
		set("material", "paper");
		set("skill", ([
			"name": "sword",	// name of the skill
			"exp_required": 200000, // minimum combat experience required
			"jing_cost":    40,     // jing cost every time study this
			"difficulty":   40,     // the base int to learn this skill
			"max_skill":    119,    // the maximum level you can learn
			"min_skill":    100,    // the minimum level you can learn
		]) );
	}
}

