// xx-book.c

inherit ITEM;

void create()
{
	set_name("�ر�", ({ "ta ben" , "book"}));
	set_weight(300);
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("unit", "��");
		set("long", "����һ�ź���ͨ��ֽ�����泭¼��һЩ�ھ����ƺ���һ"
			    "�ֽ������Ǵ�\n���ڹ����ϡ�\n");
		set("material", "paper");
		set("skill", ([
			"name"	:  "xixing-dafa",
			"exp_required":  100000,
			"jing_cost"   :  70,
			"difficulty"  :  45,
			"max_skill"   :  200,
		]));
	}
}
