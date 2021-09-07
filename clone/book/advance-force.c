// advance_force.c

inherit ITEM;

void create()
{
	set_name("�ڹ����", ({ "force book", "book" }));
	set_weight(600);
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("unit", "��");
		set("long",
"������д�����ڹ���⣩��\n");
		set("value", 30000);
		set("material", "paper");
		set("skill", ([
			"name": 	"force",
			"exp_required":	1000,
			"jing_cost":	30,
			"difficulty":	25,
			"max_skill":	49,
			"min_skill":    20,
		]));
	}
}
