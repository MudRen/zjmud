// qing-zhuling.c ������
#include <ansi.h>
inherit ITEM;
void create()
{
	set_name(HIG"������"NOR, ({"qingzhu ling", "ling"}));
	set_weight(500);
	if( clonep() )
		set_default_object(__FILE__);
	else
	{
		set("unit", "��");
		set("long","����һ�����������ɵ�����,�ɾŴ����ϼ���ǩ��,ƾ���Ƶ��ӿ�������ͬ�Ŵ�ʦ����ս��\n");
		set("value", 0);
		set("material", "steel");
	}
}
