// basic_staff.c

inherit ITEM;

void create()
{
	set_name("�ȷ�����", ({ "staff book", "book" }));
	set_weight(600);
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("unit", "��");
		set("long",
"������д�����ȷ����ţ���\n");
		set("value", 10000);
		set("material", "paper");
		set("skill", ([
			"name": 	"staff",
			"exp_required":	1000,
			"jing_cost":	20,
			"difficulty":	20,
			"max_skill":	19,
		]));
	}
}
