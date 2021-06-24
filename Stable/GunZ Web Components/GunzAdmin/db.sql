DROP TABLE IF EXISTS report_abuse_info;

/* 119 �Ű� ���� */
CREATE TABLE report_abuse_info
(
	rid				int DEFAULT '0' NOT NULL auto_increment primary key,
	reporter		varchar(24),
	filename		varchar(64),
	title			varchar(64),
	comment			text,		/* ä�� ���� */
	admin_comment	text,		/* ������ �ڸ�Ʈ */
	state			int,		/* 0: �ű�, 1: ó����, 2: �Ű�ƴ� */
	regdate			datetime
);

