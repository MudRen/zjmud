// huanshou_di.c

inherit ITEM;

void create()
{
	set_name("����֮��",({ "shoushao", "shao" }) );
	set_weight(100);
	set("icon","00980");
	set("no_sell", "���ǻ��޵Ļ������������ġ�\n");
	set("no_drop", "�������������뿪�㡣\n");
	set("no_give","�ⶫ�������Ը����ˡ� \n");
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "��");
		set("value", 100);
		set("material", "bamboo");
		set("long", "�����ٻ�����ʹ�õ����ӡ�\n");
	      }
	setup();
}

