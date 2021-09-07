// �����ʾ����avoid.c

#include <ansi.h>
#include <quest.h>
#include <command.h>

inherit QUEST_OB;

#define ZONE	    my["zone"]      // ���ն�������������

// ������󴴽�
void create()
{
	seteuid(getuid());
	setup();
}

// ������ʾ��Ϣ���񣺷������������������ô���ѯ�ʵĻ���
// �п��ܴ�������Ӧ����Ϣ��
//
// �����������env ����������صĳ�����������������������
// ��ô��ֻ�к����������ͬһ���������Ϣ��ͨ��ʿ���ܹ���֪
// ���������֧�ֵ���Ϣ��
//
// �ڵ��������ʼ���ĺ���֮ǰ�������߱����ȴ����������Ҫɢ
// ������Ϣ����ͨ������/rumor���ӳ�������ʵ�֡�������Ҫɢ
// ����λ�á������Ϣ������Ҫ���á�/rumor/λ�á�Ϊλ����Ϣ��
void init_quest(string quest_name, object env)
{
	mapping my;
	string zone;

	my = query_entire_dbase();

	// �������������
	set_name(quest_name);

	// ��������
	if (objectp(env))
	{
		zone = base_name(env);
		if (sscanf(zone, "/d/%s/%*s", zone) == 2)
			zone = "/d/" + zone + "/";
		else
			zone = "/";
	} else
		zone = "/";
	ZONE = zone;

	// �л�������״̬
	change_status(QUEST_READY);

	// ������������ʱ�䣺60����
	set("live_time", 3600);

	// �Ǽ�ҥ����Ϣ
	register_information();
}

// �������
string query_introduce(object knower)
{
	return query("introduce");
}

// �ǼǸ��������Ϣ
void register_information()
{
	mapping my = query_entire_dbase();
	mapping rumor;
	string  key;

	if (! clonep() || ! mapp(my))
		// �����������Բ��Ǽ�
		return;

	if (! mapp(rumor = query("rumor")))
		// û�п���ɢ������Ϣ
		return;

	// �Ǽ����п���ɢ������Ϣ
	foreach (key in keys(rumor))
	{
		if (! stringp(key))
			continue;

		set_information(key, rumor[key]);
	}
}

// ���������Ա�ĳ��ɢ����
int can_know_by(object knower)
{
	mapping my = query_entire_dbase();
	string fname;

	fname = file_name(environment(knower));
	if (! stringp(ZONE) || strlen(ZONE) < 1 ||
	    ZONE == fname[0..strlen(ZONE) - 1])
		// ��С����ͬһ������
		return 1;

	return 0;
}

// ���ܱ�ɢ��
int can_rumor_by()
{
	return 0;
}
