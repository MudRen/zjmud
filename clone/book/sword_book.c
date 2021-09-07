// sword_book.c

inherit ITEM;

void create()
{
	set_name("��ɽ����", ({ "sword book", "book" }));
	set_weight(600);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "��");
		set("long",
"������д������ɽ���� -- ��һ�����ţ���\n");
		set("value", 100);
		set("material", "paper");
		set("skill", ([
			"name": 	"sword",
			"exp_required":	1000,
			"jing_cost":	20,
			"difficulty":	20,
			"max_skill":	30,
		]));
	}
}
