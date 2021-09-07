// advance_whip.c

inherit ITEM;

void create()
{
	set_name("�޷����", ({ "whip book", "book" }));
	set_weight(600);
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("unit", "��");
		set("long",
"������д�����޷���⣩��\n");
		set("value", 30000);
		set("material", "paper");
		set("skill", ([
			"name": 	"whip",
			"exp_required":	1000,
			"jing_cost":	30,
			"difficulty":	25,
			"max_skill":    49,
			"min_skill":    20,
		]));
	}
}
