// expert_staff.c

inherit ITEM;

void create()
{
	set_name("�ȷ���Ҫ", ({ "staff book", "book" }));
	set_weight(600);
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("unit", "��");
		set("long",
"������д�����ȷ���Ҫ����\n");
		set("value", 50000);
		set("material", "paper");
		set("skill", ([
			"name": 	"staff",
			"exp_required":	1000,
			"jing_cost":	50,
			"difficulty":	30,
			"max_skill":	99,
			"min_skill":    20,
		]));
	}
}
