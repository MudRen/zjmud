// expert_dodge.c

inherit ITEM;

void create()
{
	set_name("�Ṧ��Ҫ", ({ "dodge book", "book" }));
	set_weight(600);
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("unit", "��");
		set("long",
"������д�����Ṧ��Ҫ����\n");
		set("value", 50000);
		set("material", "paper");
		set("skill", ([
			"name": 	"dodge",
			"exp_required":	1000,
			"jing_cost":	50,
			"difficulty":	30,
			"max_skill":	99,
			"min_skill":    20,
		]));
	}
}
