// lazhu.c

inherit ITEM;

void create()
{
	set_name( "����", ({ "zhu", "lazhu" }) );
	set_weight(10);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "ֻ");
		set("long", "����һֻ��ͨ��������������һЩ���ƣ����ȽϾ��¡�\n");
	}
	setup();
}

void init()
{
	call_out("dest", 1800);
}

void dest()
{
	write("��ǰ���һ�������ã�����Ϩ���ˡ�\n");
	destruct(this_object());
}
